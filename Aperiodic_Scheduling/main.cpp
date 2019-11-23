#include "mainwindow.h"
#include "QPainter"
#include <QApplication>
#include <QBoxLayout>
#include "Frontend/graphdisplay.h"
#include "Backend/periodictask.h"
#include "Backend/aperiodictask.h"
#include "Backend/aperiodicscheduler.h"
#include "Backend/pollingserver.h"
#include "QTest"
#include "backendmanualtestspollingserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    //BackendManualTestsPollingServer* bt = new BackendManualTestsPollingServer(nullptr);
//    //QTest::qExec(bt);

//    //Ti {ci, pi}, Ai {ri, ci, di}
//    PeriodicTask per_tasks[3];
//    AperiodicTask aper_tasks[1];
//    //T1 = {4,10};
//    per_tasks[0].setComputation_time(4);
//    per_tasks[0].setPeriod(8);
//    //T2 = {4,20};
//    per_tasks[1].setComputation_time(4);
//    per_tasks[1].setPeriod(7);
//    //T3 = {4, 5};
//    per_tasks[2].setComputation_time(4);
//    per_tasks[2].setPeriod(4);

//    //A1 {0,2,10}
//    aper_tasks[0].setReady_time(0);
//    aper_tasks[0].setComputation_time(2);
//    aper_tasks[0].setDeadline(10);


//    PollingServer* ps = new PollingServer(aper_tasks, per_tasks, 1, 3);


    return a.exec();
}
