#include "aperiodictask.h"

AperiodicTask::AperiodicTask(int r, int c, int d)
{
    this->setDeadline(d);
    this->setReady_time(r);
    this->setComputation_time(c);
    this->setRemaining_cpu_time(c);
    this->setFinish_time(0);
}

int AperiodicTask::getComputation_time() const
{
    return computation_time;
}

void AperiodicTask::setComputation_time(int value)
{
    computation_time = value;
}

int AperiodicTask::getRemaining_cpu_time() const
{
    return remaining_cpu_time;
}

void AperiodicTask::setRemaining_cpu_time(int value)
{
    remaining_cpu_time = value;
}

int AperiodicTask::getDeadline() const
{
    return deadline;
}

void AperiodicTask::setDeadline(int value)
{
    deadline = value;
}

int AperiodicTask::getReady_time() const
{
    return ready_time;
}

void AperiodicTask::setReady_time(int value)
{
    ready_time = value;
}

int AperiodicTask::getFinish_time() const
{
    return finish_time;
}

void AperiodicTask::setFinish_time(int value)
{
    finish_time = value;
}
