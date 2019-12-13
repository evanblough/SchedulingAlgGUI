#ifndef MANUALTESTS_H
#define MANUALTESTS_H

#include <QObject>
#include <QTest>
#include "Backend/pollingserver.h"


class BackendManualTestsPollingServer: public QObject
{
    Q_OBJECT
public:
    BackendManualTestsPollingServer(QObject *parent);
    static int* generate_schedule(int* size, QString filename);
    static bool results(AperiodicScheduler* ps, int len, int* sched, bool expected, int i, int* finish_times);
    static QString result_messages(int i);
private slots:
    void aperiodic_fail_one();
    void periodic_fail_one();
    void feasible_schedule_one();
    void feasible_schedule_two();
    void feasible_schedule_three();
    void feasible_schedule_four();
    void initTestCase();
    void init();
    void cleanup();
private:



};

#endif // MANUALTESTS_H
