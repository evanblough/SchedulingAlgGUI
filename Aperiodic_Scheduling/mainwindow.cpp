#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent, QWidget* schedule_panel, QWidget* workload_panel, QWidget* analysis_panel, QWidget* display_adjuster)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scrollArea->setWidget(schedule_panel);
    ui->scrollArea_2->setWidget(workload_panel);
    ui->scrollArea_3->setWidget(analysis_panel);
    ui->scrollArea_4->setWidget(display_adjuster);

}

MainWindow::~MainWindow()
{
    delete ui;
}



