#ifndef TASK_H
#define TASK_H

#include <QObject>

class Task
{
public:
    Task() {}
    Task(int c, int d, int p);
    int getComputation_time() const;

    int getDeadline() const;

    int getPeriod() const;

    int getRemaining_cpu_time() const;

    void setRemaining_cpu_time(int value);

    void setComputation_time(int value);

    void setDeadline(int value);

    void setPeriod(int value);

private:
    int computation_time;
    int deadline;
    int period;
    int remaining_cpu_time;
};

#endif // TASK_H
