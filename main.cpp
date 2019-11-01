#include "mainwindow.h"
#include "QPainter"
#include <QApplication>
#include <QBoxLayout>
#include "task.h"
#include "edfscheduler.h"
#include "graphdisplay.h"
#include "periodictask.h"
#include "aperiodictask.h"
#include "aperiodicscheduler.h"
#include "pollingserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    PeriodicTask per_tasks[1] ;
    AperiodicTask aper_tasks[3];
    per_tasks[0].setPeriod(10);
    per_tasks[0].setComputation_time(3);
    aper_tasks[0].setReady_time(0);
    aper_tasks[1].setReady_time(0);
    aper_tasks[2].setReady_time(0);
    aper_tasks[0].setComputation_time(2);
    aper_tasks[1].setComputation_time(2);
    aper_tasks[2].setComputation_time(2);
    aper_tasks[0].setDeadline(10);
    aper_tasks[1].setDeadline(20);
    aper_tasks[2].setDeadline(30);

    PollingServer* ps = new PollingServer(aper_tasks, per_tasks, 3, 1);
    ps->perform_scheduability_test();
    printf(ps->getScheduable() ? "true\n" : "false\n");








    return a.exec();
}
