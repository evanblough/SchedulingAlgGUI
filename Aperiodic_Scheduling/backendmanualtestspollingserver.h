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
private slots:
    void workload_one_test();
    void initTestCase();
    void init();
    void cleanup();
private:
    bool results(PollingServer* ps, int len, int* sched, bool* expected, int i);
    QString result_messages(int i);

};

#endif // MANUALTESTS_H
