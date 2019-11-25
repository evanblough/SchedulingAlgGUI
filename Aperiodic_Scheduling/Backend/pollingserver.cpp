#include "pollingserver.h"
#include "stdlib.h"
#include <cmath>
#include <queue>
#include <vector>
#include <iostream>
#include "Backend/deadlinecomparator.h"

int gcd(int a, int b);


/**
 * @brief PollingServer::PollingServer
 * This class is an extension of the Aperiodic scheduler class.
 * This class holds methods that generate schedule objects accoridng to polling server algorithim conventions.
 * This class emulates the function of a polling server scheduling algorithim.
 * @param aper_tasks
 * This parameter is an array of aperodic task objects. Each object holds data fields like period and computation time.
 * @param per_tasks
 * This parameter is an array of periodic task objects.
 * @param num_aper_tasks
 * This parameter indicates the length of the aperiodic task array
 * @param num_per_tasks
 * This parameter indicates the length of the periodic task array
 */

PollingServer::PollingServer(AperiodicTask* aper_tasks, PeriodicTask* per_tasks, int num_aper_tasks, int num_per_tasks, int alloted_server_index)
{
    //Use Params to fill fields
    this->setAper_tasks(aper_tasks);
    this->setPer_tasks(per_tasks);
    this->setNum_per_tasks(num_per_tasks);
    this->setNum_aper_tasks(num_aper_tasks);
    this->setSchedule(nullptr);
    this->setScheduable(true);
    this->setAlloted_server(&per_tasks[alloted_server_index]);
    this->setAlloted_server_index(alloted_server_index);
    //Use methods to fill fields
    this->perform_scheduability_test();
    this->produce_schedule();
    this->perform_scheduability_test();

}

/**
 * @brief PollingServer::produce_schedule
 * This function populates the schedule integer array with a correct schedule
 */
void PollingServer::produce_schedule(){

    this->setScheduable(true);

    //Calculate Length of Schedule
    this->setSchedule_length(this->calculate_sched_len());

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

    //Create flag to only execute one aperiodic task at a time
    bool active_flag = false;

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

        //Check at server instance for enqueued tasks
        if(time % this->getAlloted_server()->getPeriod() == 0){
            //If tasks in queue activate
            if(!aper_queue.empty()){
                active_flag = true;
                this->getAlloted_server()->setRemaining_cpu_time(this->getAlloted_server()->getComputation_time());
            }
            else{
                //No tasks in queue, so sleep allocated server
                active_flag = false;
                this->getAlloted_server()->setRemaining_cpu_time(0);
            }
         }

        //Schedule task with closest period; Assuming periodic tasks are ordered in order of period
        for(int i = 0; i < this->getNum_per_tasks(); i++){
            //If Alloted Server Running
            if(i == this->getAlloted_server_index() && this->getAlloted_server()->getRemaining_cpu_time() > 0){
                //If tasks were enqueued
                if(active_flag){
                    //Check if a_current set
                    if(a_current.getReady_time() == -1){
                        a_current = aper_queue.top();
                        aper_queue.pop();
                    }
                    //Run task
                    this->getAlloted_server()->setRemaining_cpu_time(this->getAlloted_server()->getRemaining_cpu_time()-1);
                    a_current.setRemaining_cpu_time(a_current.getRemaining_cpu_time()-1);
                    this->getSchedule()[time] = this->getAlloted_server_index();
                    if(a_current.getRemaining_cpu_time() == 0){
                        a_current.setReady_time(-1);
                        if(aper_queue.empty()){
                            active_flag = false;
                        }
                    }

                }

            }
            //Periodic Task running
            else if(this->getPer_tasks()[i].getRemaining_cpu_time() > 0){
                this->getSchedule()[time] = i;
                this->getPer_tasks()[i].setRemaining_cpu_time(this->getPer_tasks()[i].getRemaining_cpu_time()-1);
                break;
            }
            //Task Not Ran
            else {

            }
        }

    }




}

/**
 * @brief PollingServer::perform_scheduability_test
 * This function checks the aperiodic and periodic scheduability of the given workload that was supplied in this instance of a Polling Server Object
 */
void PollingServer::perform_scheduability_test(){
    this->setScheduable(false);
    //If periodic workload pass
    if(periodic_scheduability()){
        //Set scheduable to true if guranteed otherwise set to result of exact analysis
        setScheduable(aperiodic_scheduability() || this->getScheduable());
    }
}

//TODO Fix Scheduability Tests
/**
 * @brief PollingServer::aperiodic_scheduability
 * Used by perform_scheduability_test() to populate the schedubale field.
 * @return returns a boolean value coresponding to whether the aperiodic workload is able to be scheduled
 */
bool PollingServer::aperiodic_scheduability(){
   //For every aperiodic task ensure that following condition is met
   AperiodicTask ai;
    for(int i = 0; i < this->getNum_aper_tasks(); i++){
        ai = this->getAper_tasks()[i];
        int Ps = this->getAlloted_server()->getPeriod();
        double ca_cs = double(ai.getComputation_time())/double(this->getAlloted_server()->getComputation_time());
        int ceil_ = ceil(ca_cs);

        //Ps + ceil(Ca/Cs)*Ps<=Da ==> Scheduling Guranteed
        int Da = ai.getDeadline();
        if(Ps + ceil_*Ps > Da){
            return true;
        }

    }
    return true;
}

/**
 * @brief PollingServer::periodic_scheduability
 * Used by perform_scheduability_test() to populate the schedubale field.
 * @return returns a boolean value coresponding to whether the periodic workload is able to be scheduled.
 */
bool PollingServer::periodic_scheduability(){
    PeriodicTask ti;
    double sum_computation = 0.0;
    for(int i = 0; i < this->getNum_per_tasks(); i++){
        ti = this->getPer_tasks()[i];
        sum_computation += ((double)ti.getComputation_time())/((double)ti.getPeriod());
    }
    return (sum_computation <= this->getNum_per_tasks()*(pow(2.0, 1.0/this->getNum_per_tasks())-1));

}

/**
 * @brief PollingServer::calculate_sched_len
 * This function is used to calculate the length of the schedule to be calculated. In order to prevent
 * uncessary computations, the combined schedulers only calculate task allocation when it is not easily predictable.
 * This will calculate when the last aperiodic task will finish and the next LCM cycle of periods. After the aperiodic load
 * is finished the tasks will simply repeat according to RMS (Rate Monotonic Scheduling) convetions.
 * @return Returns the length of the schedule array.
 */
int PollingServer::calculate_sched_len(){

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


/**
 * @brief PollingServer::calculate_lcm This function calculates the lcm of task periods.
 * @param periods an array of the period refresh time of each periodic task within the polling server object.
 * @param n the length of the periods array
 * @return the lcm of the periods
 */

int PollingServer::calculate_lcm(int* periods, int n){
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



