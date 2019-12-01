#include "workloadwindow.h"
#include "ui_workloadwindow.h"

WorkloadWindow::WorkloadWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkloadWindow)
{
    ui->setupUi(this);
    this->setAperiodic_file_name(this->ui->aperiodic_filename);
    this->setPeriodic_file_name(this->ui->periodic_filename);
    this->setFile_input_button(this->ui->file_input_button);

}

WorkloadWindow::~WorkloadWindow()
{
    delete ui;
}

QPushButton *WorkloadWindow::getFile_input_button() const
{
    return file_input_button;
}

void WorkloadWindow::setFile_input_button(QPushButton *value)
{
    file_input_button = value;
}

QPushButton *WorkloadWindow::getManual_input_button() const
{
    return manual_input_button;
}

void WorkloadWindow::setManual_input_button(QPushButton *value)
{
    manual_input_button = value;
}

QPlainTextEdit *WorkloadWindow::getPeriodic_file_name() const
{
    return periodic_file_name;
}

void WorkloadWindow::setPeriodic_file_name(QPlainTextEdit *value)
{
    periodic_file_name = value;
}

QPlainTextEdit *WorkloadWindow::getAperiodic_file_name() const
{
    return aperiodic_file_name;
}

void WorkloadWindow::setAperiodic_file_name(QPlainTextEdit *value)
{
    aperiodic_file_name = value;
}


