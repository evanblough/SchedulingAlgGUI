#include "pollingserver.h"
#include "stdlib.h"
#include <cmath>


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

PollingServer::PollingServer(AperiodicTask* aper_tasks, PeriodicTask* per_tasks, int num_aper_tasks, int num_per_tasks)
{
    //Use Params to fill fields
    this->setAper_tasks(aper_tasks);
    this->setPer_tasks(per_tasks);
    this->setNum_per_tasks(num_per_tasks);
    this->setNum_aper_tasks(num_aper_tasks);
    this->setSchedule(nullptr);
    this->setScheduable(true);
    this->setAlloted_server(&per_tasks[num_per_tasks-1]);
    //Use methods to fill fields
    this->perform_scheduability_test();
    this->produce_schedule();




}

/**
 * @brief PollingServer::produce_schedule
 * This function populates the schedule integer array with a correct schedule
 */
void PollingServer::produce_schedule(){
    this->setScheduable(true);

    //Calculate Length of Schedule
    this->calculate_sched_len();




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
            //Perform Exact Analysis to confirm scheduability

            return false;
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
    //printf("%f\n", sum_computation);
    //printf("%f\n", this->getNum_per_tasks()*(pow(2.0, 1.0/this->getNum_per_tasks())-1));
    return (sum_computation <= this->getNum_per_tasks()*(pow(2.0, 1.0/this->getNum_per_tasks())-1));

}

int PollingServer::calculate_sched_len(){
    int periods[this->getNum_per_tasks()];
    for(int i = 0; i < this->getNum_per_tasks(); i++){
        periods[i] = (this->getPer_tasks()+i)->getPeriod();
    }
    int lcm = this->calculate_lcm(periods, this->getNum_per_tasks());
    return 0;
}





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



