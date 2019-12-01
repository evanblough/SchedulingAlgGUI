#include "workloadwindow.h"
#include "ui_workloadwindow.h"

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

