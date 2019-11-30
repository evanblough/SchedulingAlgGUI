#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller.h"
#include "Frontend/workloadwindow.h"

MainWindow::MainWindow(QWidget* parent, QWidget* schedule_panel, WorkloadWindow* workload_panel, QWidget* analysis_panel, QWidget* display_adjuster, QObject* controller)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scrollArea->setWidget(schedule_panel);
    ui->scrollArea_2->setWidget(workload_panel);
    ui->scrollArea_3->setWidget(analysis_panel);
    ui->scrollArea_4->setWidget(display_adjuster);

    this->schedule_panel = schedule_panel;
    this->workload_panel = workload_panel;
    this->analysis_panel = analysis_panel;
    this->display_adjuster = display_adjuster;
    this->controller = controller;

    connect_sigs();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connect_sigs(){

}



