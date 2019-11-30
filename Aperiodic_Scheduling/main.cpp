#include "mainwindow.h"
#include "QPainter"
#include <QApplication>
#include <QBoxLayout>
#include "Frontend/graphdisplay.h"
#include "Backend/periodictask.h"
#include "Backend/aperiodictask.h"
#include "Backend/aperiodicscheduler.h"
#include "Backend/pollingserver.h"
#include "Backend/deadlinecomparator.h"
#include "QTest"
#include "backendmanualtestspollingserver.h"
#include <queue>
#include <vector>
#include <bits/stdc++.h>
#include "Frontend/workloadwindow.h"
#include "Frontend/analysiswindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PeriodicTask per_workload[3];
    AperiodicTask aper_workload[3];

    //T1 = {1,4};
    per_workload[0].setComputation_time(1);
    per_workload[0].setRemaining_cpu_time(1);
    per_workload[0].setPeriod(4);

    //T2 = {1,8};
    per_workload[1].setComputation_time(1);
    per_workload[1].setRemaining_cpu_time(1);
    per_workload[1].setPeriod(8);

    //Ts = {3, 8}
    per_workload[2].setComputation_time(3);
    per_workload[2].setRemaining_cpu_time(3);
    per_workload[2].setPeriod(8);

    //A0 = {0,2,10}
    aper_workload[0].setReady_time(0);
    aper_workload[0].setComputation_time(2);
    aper_workload[0].setRemaining_cpu_time(2);
    aper_workload[0].setDeadline(10);
    aper_workload[0].setIndex(0);

    //A1 = {0,1,11}
    aper_workload[1].setReady_time(0);
    aper_workload[1].setComputation_time(1);
    aper_workload[1].setRemaining_cpu_time(1);
    aper_workload[1].setDeadline(11);
    aper_workload[1].setIndex(1);

    //A2 = {0, 2, 16}
    aper_workload[2].setReady_time(0);
    aper_workload[2].setComputation_time(2);
    aper_workload[2].setRemaining_cpu_time(2);
    aper_workload[2].setDeadline(16);
    aper_workload[2].setIndex(2);

    PollingServer* ps = new PollingServer(aper_workload, per_workload, 3, 3, 2);
    printf("%d\n", ps->getSchedule_length());
    GraphDisplay* g = new GraphDisplay(nullptr, ps->getSchedule(), ps->getSchedule_length(), ps->getNum_per_tasks(), ps->getSchedule_length(), ps->getNum_per_tasks() + 1, 500);
    QColor colors[7];
    colors[0].setNamedColor("#BFFBFF"); //Pale Blue
    colors[1].setNamedColor("#1FCBFF"); //Teal
    colors[2].setNamedColor("#2B95FF"); //Carolina Blue
    colors[3].setNamedColor("#3414FF"); //Blue
    colors[4].setNamedColor("#7A05FF"); //Purp
    colors[5].setNamedColor("#065951"); //Dark Teal
    colors[6].setNamedColor("#292629"); //Dark Grey

    g->setFixedSize(3000, 1000);

    QPalette* palette = new QPalette(colors[1], colors[6], colors[0], colors[5], colors[2], colors[0], colors[6]);
    g->setPalette(*palette);

    AnalysisWindow* aw = new AnalysisWindow();

    WorkloadWindow* ww = new WorkloadWindow();
    ww->setPalette(*palette);

    MainWindow* w = new MainWindow(nullptr, g, ww, aw);
    w->setPalette(*palette);
    w->show();







    //BackendManualTestsPollingServer* bt = new BackendManualTestsPollingServer(nullptr);
    //QTest::qExec(bt);



    return a.exec();
}
