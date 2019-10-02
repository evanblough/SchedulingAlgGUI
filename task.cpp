#include "task.h"

Task::Task(int c, int d, int p)
{
    this->computation_time = c;
    this->deadline = d;
    this->period = p;
    this->remaining_cpu_time = c;
}

int Task::getComputation_time() const
{
    return computation_time;
}


int Task::getDeadline() const
{
    return deadline;
}

int Task::getPeriod() const
{
    return period;
}

int Task::getRemaining_cpu_time() const
{
    return remaining_cpu_time;
}

void Task::setRemaining_cpu_time(int value)
{
    remaining_cpu_time = value;
}

void Task::setComputation_time(int value)
{
    computation_time = value;
}

void Task::setDeadline(int value)
{
    deadline = value;
}

void Task::setPeriod(int value)
{
    period = value;
}
