#ifndef DEFFERABLESERVER_H
#define DEFFERABLESERVER_H
#include "Backend/aperiodicscheduler.h"


class DefferableServer : public AperiodicScheduler
{
public:
    DefferableServer();
    DefferableServer(AperiodicTask* aper_tasks, PeriodicTask* per_tasks, int num_aper_tasks, int num_per_tasks, int alloted_server_index);
    void produce_schedule();
    void perform_scheduability_test();
    bool aperiodic_scheduability();
    bool periodic_scheduability();
private:
    int calculate_sched_len();
    int calculate_lcm(int* periods, int n);
};

#endif // DEFFERABLESERVER_H
