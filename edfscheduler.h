#ifndef EDFSCHEDULER_H
#define EDFSCHEDULER_H

#include <QObject>
#include "task.h"

class EDFScheduler : public QObject
{
    Q_OBJECT
public:
    explicit EDFScheduler(QObject *parent = nullptr, Task* tasks = nullptr, int num_of_tasks =0);
    int * schedule;
    int num_tasks;
    int time_len;
signals:

public slots:

private:
int gcd(int a, int b);
};

#endif // EDFSCHEDULER_H
