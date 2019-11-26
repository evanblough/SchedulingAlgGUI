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
    BackendManualTestsPollingServer* bt = new BackendManualTestsPollingServer(nullptr);
    QTest::qExec(bt);



    return a.exec();
}
