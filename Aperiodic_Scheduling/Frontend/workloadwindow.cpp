#include "workloadwindow.h"
#include "ui_workloadwindow.h"

/**
 * @brief WorkloadWindow::WorkloadWindow This is a QWidget Class with an associated QML layout file.
 * This window has a ui file that has pointers to the ui elements of the workload window used in the mainwindow.
 * This window allows users to input aperiodic and periodic inputs by supplying csv files or manually inputing parameters.
 * @param parent
 */
WorkloadWindow::WorkloadWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkloadWindow)
{
    ui->setupUi(this);
}

WorkloadWindow::~WorkloadWindow()
{
    delete ui;
}

Ui::WorkloadWindow *WorkloadWindow::getUi() const{
    return this->ui;
}

