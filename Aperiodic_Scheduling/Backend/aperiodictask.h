#ifndef APERIODICTASK_H
#define APERIODICTASK_H

#include <QObject>

class AperiodicTask
{
public:
    AperiodicTask(){}
    AperiodicTask(int r, int c, int d);

    int getComputation_time() const;
    void setComputation_time(int value);

    int getRemaining_cpu_time() const;
    void setRemaining_cpu_time(int value);

    int getDeadline() const;
    void setDeadline(int value);

    int getReady_time() const;
    void setReady_time(int value);

    int getFinish_time() const;
    void setFinish_time(int value);

private:
    int computation_time, remaining_cpu_time, deadline, ready_time, finish_time;

};

#endif // APERIODICTASK_H
