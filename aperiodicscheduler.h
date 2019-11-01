#ifndef APERIODICSCHEDULER_H
#define APERIODICSCHEDULER_H

#include <QObject>

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

private:
    int* schedule;
    int schedule_length;
    bool scheduable;
};

#endif // APERIODICSCHEDULER_H
