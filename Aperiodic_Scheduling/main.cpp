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
#include "backendmanualtestsdefferableserver.h"
#include <queue>
#include <vector>
#include <bits/stdc++.h>
#include "Frontend/workloadwindow.h"
#include "Frontend/analysiswindow.h"
#include "Frontend/displayadjuster.h"
#include "controller.h"
#include "ui_analysiswindow.h"
#include "Backend/defferableserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BackendManualTestsPollingServer* bt = new BackendManualTestsPollingServer(nullptr);
    BackendManualTestsDefferableServer* ds = new BackendManualTestsDefferableServer();
    QTest::qExec(bt);
    printf("\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n\n");
    QTest::qExec(ds);

    //Color Pallete
    QColor colors[7];
    colors[0].setNamedColor("#BFFBFF"); //Pale Blue
    colors[1].setNamedColor("#1FCBFF"); //Teal
    colors[2].setNamedColor("#2B95FF"); //Carolina Blue
    colors[3].setNamedColor("#3414FF"); //Blue
    colors[4].setNamedColor("#7A05FF"); //Purp
    colors[5].setNamedColor("#065951"); //Dark Teal
    colors[6].setNamedColor("#292629"); //Dark Grey

    QPalette* palette = new QPalette(colors[1], colors[6], colors[0], colors[5], colors[2], colors[0], colors[6]);

    //Setup Child Windows and Controller Object
    AnalysisWindow* aw = new AnalysisWindow();
    WorkloadWindow* ww = new WorkloadWindow(nullptr);
    DisplayAdjuster* da = new DisplayAdjuster();
    GraphDisplay* gd = new GraphDisplay();
    //gd->setFixedSize(30000, 500);

    Controller* controller = new Controller(nullptr, ww, aw, da, gd);

    //Launch main window after all preconfiguration
    MainWindow* w = new MainWindow(nullptr, gd, ww, aw, da);
    w->setPalette(*palette);
    w->show();

    //Highlight run button
    colors[6] = colors[1];
    colors[0].setNamedColor("#292629"); //Dark Grey
    palette = new QPalette(colors[1], colors[6], colors[0], colors[5], colors[2], colors[0], colors[6]);
    aw->getUi()->run_analysis->setPalette(*palette);



    return a.exec();
}
