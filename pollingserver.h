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
    PollingServer(AperiodicTask* aper_tasks, PeriodicTask* per_tasks, int num_aper_tasks, int num_per_tasks);
    void produce_schedule();
    void perform_scheduability_test();
private:
    AperiodicTask* aper_tasks;
    PeriodicTask* per_tasks;
    int num_aper_tasks, num_per_tasks;
    PeriodicTask* alloted_server;
};

#endif // POLLINGSERVER_H