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
    this->setScheduable(true);

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
            this->setScheduable(false);
            return;
        }

    }
    //Workload is scheduable
}



