#include "workloadwindow.h"
#include "ui_workloadwindow.h"

WorkloadWindow::WorkloadWindow(QWidget *parent, Controller* controller) :
    QWidget(parent),
    ui(new Ui::WorkloadWindow)
{
    ui->setupUi(this);
    this->controller = controller;
    this->setFile_name(this->ui->aperiodic_filename);
    connect_sigs();

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


void WorkloadWindow::connect_sigs(){
    QObject::connect(this->ui->file_input_button, &QPushButton::clicked, this->controller, &Controller::file_input_selected);
}

QPlainTextEdit *WorkloadWindow::getFile_name() const
{
    return file_name;
}

void WorkloadWindow::setFile_name(QPlainTextEdit *value)
{
    file_name = value;
}
