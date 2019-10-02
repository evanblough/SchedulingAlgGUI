#include "edfscheduler.h"
#include "task.h"

int return_lcm(int *periods, int n);
int gcd(int a, int b);

EDFScheduler::EDFScheduler(QObject *parent, Task* tasks, int num_of_tasks) : QObject(parent)
{
    //Get periods
    int a[num_of_tasks];
    for(int i = 0; i < num_of_tasks; i++){
        a[i] = (tasks + i)->getPeriod();
    }

    //Calculate LCM
    int lcm = return_lcm(a, num_of_tasks);
    printf("LCM :%d\n", lcm);

    int schedule[num_of_tasks][lcm];
    //Populate schedule with null values
    for(int i =0; i < lcm; i++){
        for(int j =0; j < num_of_tasks; j++){
            schedule[j][i] = 0;
        }
    }

    //Iterate through tasks for LCM
    for(int i = 0; i < lcm; i++){
        //find earliest deadline
        printf("Time : %d\n", i);
        int earliest_deadline = 10000000;
        int earliest_deadline_index = 0;
        for(int j = 0; j < num_of_tasks; j++){
            printf("Evaluating task %d\n", j);
            //Refresh CPU time if task re-enters
            if(i % tasks[j].getPeriod() == 0){
                printf("Comp Time refresh for task %d\n", j);
                tasks[j].setRemaining_cpu_time(tasks[j].getComputation_time());
            }
            //Select ED given that has computation time left
            if(earliest_deadline > tasks[j].getDeadline() && tasks[j].getRemaining_cpu_time() > 0){
                earliest_deadline = tasks[j].getDeadline();
                earliest_deadline_index = j;
                printf("Task %d choosen\n", earliest_deadline_index);
            }
        }
        if(tasks[earliest_deadline_index].getRemaining_cpu_time() != 0){
        //Schedule Task for one unit of time
        schedule[earliest_deadline_index][i] = 1;
        //Update remaining CPU Time of scheduled task
        tasks[earliest_deadline_index].setRemaining_cpu_time((tasks+earliest_deadline_index)->getRemaining_cpu_time() - 1);
        }
    }
}

int return_lcm(int *periods, int n){
    int result = *periods;
    for(int i = 1; i < n; i++){
        result = (((periods[i]*result)) / gcd(periods[i], result));
    }
    return result;
}

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
