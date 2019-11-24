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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    AperiodicTask workload[7];
    workload[0].setDeadline(10);
    workload[1].setDeadline(5);
    workload[2].setDeadline(5);
    workload[3].setDeadline(8);
    workload[4].setDeadline(9);
    workload[5].setDeadline(4);
    workload[6].setDeadline(6);
    std::priority_queue<AperiodicTask, std::vector<AperiodicTask>, DeadlineComparator> pq;

    for(int i = 0; i < 7; i++){
        pq.push(workload[i]);
    }

    for(int i = 0; i < 7; i++){
        printf("Pop %d: %d\n", i, pq.top().getDeadline());
        pq.pop();
    }



    return a.exec();
}
