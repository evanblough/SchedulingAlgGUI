#ifndef BACKENDMANUALTESTSDEFFERABLESERVER_H
#define BACKENDMANUALTESTSDEFFERABLESERVER_H
#define TESTFOLDER "/home/rmasl/Desktop/Evan_Personal_Use/SchedulingAlgDisplay/SchedulingAlgDisplay/Aperiodic_Scheduling/InputFiles/DefferableServerTests/"


#include <QObject>
#include <QTest>

class BackendManualTestsDefferableServer : public QObject
{
    Q_OBJECT
public:
    explicit BackendManualTestsDefferableServer(QObject *parent = nullptr);

signals:

public slots:

private slots:
    void feasible_schedule_one();
    void feasible_schedule_two();
    void feasible_schedule_three();
};

#endif // BACKENDMANUALTESTSDEFFERABLESERVER_H
