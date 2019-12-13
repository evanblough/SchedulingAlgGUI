#ifndef BACKENDMANUALTESTSDEFFERABLESERVER_H
#define BACKENDMANUALTESTSDEFFERABLESERVER_H

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
};

#endif // BACKENDMANUALTESTSDEFFERABLESERVER_H
