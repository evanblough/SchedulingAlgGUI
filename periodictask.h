#ifndef PERIODICTASK_H
#define PERIODICTASK_H

#include <QObject>

class PeriodicTask
{
public:
    PeriodicTask() {}
    PeriodicTask(int c, int p);

    int getComputation_time() const;
    void setComputation_time(int value);

    int getPeriod() const;
    void setPeriod(int value);

    int getRemaining_cpu_time() const;
    void setRemaining_cpu_time(int value);

private:
    int computation_time;
    int period;
    int remaining_cpu_time;
};

#endif // PERIODICTASK_H
