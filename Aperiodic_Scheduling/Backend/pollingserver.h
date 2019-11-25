#ifndef POLLINGSERVER_H
#define POLLINGSERVER_H

#include <QObject>
#include "aperiodicscheduler.h"
#include "periodictask.h"
#include "aperiodictask.h"
#include "stdlib.h"
#include <cmath>

class PollingServer : public AperiodicScheduler
{
public:
    PollingServer(AperiodicTask* aper_tasks, PeriodicTask* per_tasks, int num_aper_tasks, int num_per_tasks, int alloted_server_index);
    void produce_schedule();
    void perform_scheduability_test();
    bool aperiodic_scheduability();
    bool periodic_scheduability();
private:
    int calculate_sched_len();
    int calculate_lcm(int* periods, int n);
};

#endif // POLLINGSERVER_H
