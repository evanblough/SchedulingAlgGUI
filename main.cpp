#include "mainwindow.h"
#include "QPainter"
#include <QApplication>
#include "task.h"
#include "edfscheduler.h"
#include "graphdisplay.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Task tasks[3];
    tasks[0].setPeriod(10);
    tasks[0].setDeadline(5);
    tasks[0].setComputation_time(5);
    tasks[1].setPeriod(10);
    tasks[1].setDeadline(8);
    tasks[1].setComputation_time(3);
    tasks[2].setPeriod(20);
    tasks[2].setDeadline(20);
    tasks[2].setComputation_time(3);

    EDFScheduler *scheduler = new EDFScheduler(nullptr, tasks, 3);

    GraphDisplay *g = new GraphDisplay(nullptr, scheduler->schedule, scheduler->time_len, scheduler->num_tasks, 20, 10);
    g->show();


    return a.exec();
}
