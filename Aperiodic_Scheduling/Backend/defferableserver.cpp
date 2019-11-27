#include "defferableserver.h"
#include <cmath>
#include <queue>
#include <vector>
#include "deadlinecomparator.h"


int gcd(int a, int b);

DefferableServer::DefferableServer(AperiodicTask* aper_tasks, PeriodicTask* per_tasks, int num_aper_tasks, int num_per_tasks, int alloted_server_index)
{
    this->setAper_tasks(aper_tasks);
    this->setPer_tasks(per_tasks);
    this->setNum_aper_tasks(num_aper_tasks);
    this->setNum_per_tasks(num_per_tasks);
    this->setAlloted_server_index(alloted_server_index);
    this->setAlloted_server(&per_tasks[alloted_server_index]);

    this->perform_scheduability_test();
    if(this->getScheduable()){
        this->setSchedule_length(this->calculate_sched_len());
        this->produce_schedule();
    }


}

void DefferableServer::perform_scheduability_test(){
    PeriodicTask ti;
    double sum_computation = 0.0;
    for(int i = 0; i < this->getNum_per_tasks(); i++){
        ti = this->getPer_tasks()[i];
        sum_computation += ((double)ti.getComputation_time())/((double)ti.getPeriod());
    }
    this->setScheduable(sum_computation <= this->getNum_per_tasks()*(pow(2.0, 1.0/this->getNum_per_tasks())-1));

}

int DefferableServer::calculate_sched_len(){
    //Find LCM
    int periods[this->getNum_per_tasks()];
    for(int i = 0; i < this->getNum_per_tasks(); i++){
        periods[i] = (this->getPer_tasks()+i)->getPeriod();
    }
    int lcm = this->calculate_lcm(periods, this->getNum_per_tasks());
    //Find latest deadline for aperiodic task in the set
    int max_deadline = this->getAper_tasks()->getDeadline();
    for(int i = 1; i < this->getNum_aper_tasks(); i++){
        if(this->getAper_tasks()[i].getDeadline() > max_deadline)
            max_deadline = this->getAper_tasks()[i].getDeadline();
    }
    //Find multiple of LCM that is larger than last aperiodic deadline
    int sched_len = lcm;
    while(sched_len <= max_deadline){
        sched_len+= lcm;
    }
    //After the last aperiodic task executes the tasks will enter a predictable pattern

    return sched_len;
}

int DefferableServer::calculate_lcm(int *periods, int n){
    int result = *periods;
        for(int i = 1; i < n; i++){
            result = (((periods[i]*result)) / gcd(periods[i], result));
        }
        return result;
}


int gcd(int a, int b){
    if (b == 0)
        return a;

    return gcd(b, a % b);
}

void DefferableServer::produce_schedule(){

    //Initialize Finish Times
    for(int i = 0; i < this->getNum_aper_tasks(); i++){
        this->getAper_tasks()[i].setFinish_time(-1);
    }

    //Allocate memory for schedule
    this->setSchedule((int*)malloc(sizeof(int)*this->getSchedule_length()));

    //Initialize memory
    for(int i = 0;  i < this->getSchedule_length(); i++){
        this->getSchedule()[i] = -1;
    }

    //Create Aperiodic Task Queue
    std::priority_queue<AperiodicTask, std::vector<AperiodicTask>, DeadlineComparator> aper_queue;

    //Aperiodic task to be executed
    AperiodicTask a_current;
    //Flag for intialization
    a_current.setReady_time(-1);
    a_current.setRemaining_cpu_time(0);

    //Runtime Scheduling Loop
    for(int time = 0; time < this->getSchedule_length(); time++){

        //Refresh Remaining CPU time for periodic tasks for period time
        for(int i = 0; i < this->getNum_per_tasks(); i++){
            if(time % this->getPer_tasks()[i].getPeriod() == 0){
                this->getPer_tasks()[i].setRemaining_cpu_time(this->getPer_tasks()[i].getComputation_time());
            }
        }

        //Check Aperiodic FIFO Queue or Earliest deadline
        //I choose an EDF Heap pros: Prevents total system failure in more cases; cons: will result in later response time for some workloads.
        for(int i = 0; i < this->getNum_aper_tasks(); i++){
            if(time == this->getAper_tasks()[i].getReady_time()){
                aper_queue.push(this->getAper_tasks()[i]);
            }
        }

        //Get next task to run
        if(a_current.getReady_time() == -1 && !aper_queue.empty()){
            a_current = aper_queue.top();
            aper_queue.pop();
        }

        for(int i = 0; i < this->getNum_per_tasks(); i++){

            //If alloted server up and time remain execute
            if(i == this->getAlloted_server_index() && this->getAlloted_server()->getRemaining_cpu_time() > 0 && a_current.getReady_time() != -1){
                this->getSchedule()[time] = this->getAlloted_server_index();
                a_current.setRemaining_cpu_time(a_current.getRemaining_cpu_time()-1);
                this->getAlloted_server()->setRemaining_cpu_time(this->getAlloted_server()->getRemaining_cpu_time()-1);
                if(a_current.getRemaining_cpu_time() == 0){
                    a_current.setReady_time(-1);
                    this->getAper_tasks()[a_current.getIndex()].setFinish_time(time + 1);

                }
                break;
            }
            //If periodic task
            else if(this->getPer_tasks()[i].getRemaining_cpu_time() > 0){
                this->getSchedule()[time] = i;
                this->getPer_tasks()[i].setRemaining_cpu_time(this->getPer_tasks()[i].getRemaining_cpu_time()-1);
                break;
            }
            //shouldn't happen
            else{
                break;
            }


        }

    }




}
