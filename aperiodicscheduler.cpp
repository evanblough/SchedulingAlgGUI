#include "aperiodicscheduler.h"

AperiodicScheduler::AperiodicScheduler()
{

}

int *AperiodicScheduler::getSchedule() const
{
    return schedule;
}

void AperiodicScheduler::setSchedule(int *value)
{
    schedule = value;
}

int AperiodicScheduler::getSchedule_length() const
{
    return schedule_length;
}

void AperiodicScheduler::setSchedule_length(int value)
{
    schedule_length = value;
}

bool AperiodicScheduler::getScheduable() const
{
    return scheduable;
}

void AperiodicScheduler::setScheduable(bool value)
{
    scheduable = value;
}
