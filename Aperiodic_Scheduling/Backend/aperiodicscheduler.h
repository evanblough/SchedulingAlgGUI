#ifndef APERIODICSCHEDULER_H
#define APERIODICSCHEDULER_H

#include <QObject>
#include "Backend/aperiodictask.h"
#include "Backend/periodictask.h"


class AperiodicScheduler
{
public:
    AperiodicScheduler();
    int *getSchedule() const;
    void setSchedule(int *value);

    int getSchedule_length() const;
    void setSchedule_length(int value);

    bool getScheduable() const;
    void setScheduable(bool value);

    int getNum_aper_tasks() const;
    void setNum_aper_tasks(int value);

    int getNum_per_tasks() const;
    void setNum_per_tasks(int value);

    AperiodicTask *getAper_tasks() const;
    void setAper_tasks(AperiodicTask *value);

    PeriodicTask *getPer_tasks() const;
    void setPer_tasks(PeriodicTask *value);

    PeriodicTask *getAlloted_server() const;
    void setAlloted_server(PeriodicTask *value);

    int getAlloted_server_index() const;
    void setAlloted_server_index(int value);

private:
    int* schedule;
    int schedule_length, alloted_server_index;
    int num_aper_tasks, num_per_tasks;
    bool scheduable;
    AperiodicTask* aper_tasks;
    PeriodicTask* per_tasks;
    PeriodicTask* alloted_server;
};

#endif // APERIODICSCHEDULER_H
