#include "pollingserver.h"
#include "stdlib.h"
#include <cmath>

PollingServer::PollingServer(AperiodicTask* aper_tasks, PeriodicTask* per_tasks, int num_aper_tasks, int num_per_tasks)
{
    this->aper_tasks = aper_tasks;
    this->per_tasks = per_tasks;
    this->num_per_tasks = num_per_tasks;
    this->num_aper_tasks = num_aper_tasks;
    this->setSchedule(nullptr);
    this->setScheduable(true);
    this->alloted_server = &per_tasks[num_per_tasks-1];

}

void PollingServer::produce_schedule(){

}

void PollingServer::perform_scheduability_test(){
    if(periodic_scheduability()){
        setScheduable(aperiodic_scheduability());
    }
    else setScheduable(false);

}

bool PollingServer::aperiodic_scheduability(){
   //For every aperiodic task ensure that following condition is met
   AperiodicTask ai;
    for(int i = 0; i < this->num_aper_tasks; i++){
        ai = this->aper_tasks[i];
        int Ps = this->alloted_server->getPeriod();
        double ca_cs = double(ai.getComputation_time())/double(this->alloted_server->getComputation_time());
        int ceil_ = ceil(ca_cs);

        //Ps + ceil(Ca/Cs)*Ps>Da ==> Not Scheduable
        int Da = ai.getDeadline();
        if(Ps + ceil_*Ps > Da){
            return false;
        }

    }
    return true;
}

bool PollingServer::periodic_scheduability(){
    PeriodicTask ti;
    double sum_computation = 0;
    for(int i = 0; i < this->num_per_tasks; i++){
        ti = this->per_tasks[i];
        sum_computation += ti.getComputation_time()/ti.getPeriod();
    }
    return (sum_computation <= this->num_per_tasks*(pow(2.0, 1.0/this->num_per_tasks)-1));

}



