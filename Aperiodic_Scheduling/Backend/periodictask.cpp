#include "periodictask.h"

PeriodicTask::PeriodicTask(int c, int p)
{
    this->setComputation_time(c);
    this->setRemaining_cpu_time(c);
    this->setPeriod(p);

}

int PeriodicTask::getComputation_time() const
{
    return computation_time;
}

void PeriodicTask::setComputation_time(int value)
{
    computation_time = value;
}

int PeriodicTask::getPeriod() const
{
    return period;
}

void PeriodicTask::setPeriod(int value)
{
    period = value;
}

int PeriodicTask::getRemaining_cpu_time() const
{
    return remaining_cpu_time;
}

void PeriodicTask::setRemaining_cpu_time(int value)
{
    remaining_cpu_time = value;
}
