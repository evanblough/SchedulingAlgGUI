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

void WorkloadWindow::on_verticalScrollBar_sliderMoved(int position)
{

}

void WorkloadWindow::on_verticalScrollBar_valueChanged(int value)
{

}
