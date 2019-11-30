#include "workloadwindow.h"
#include "ui_workloadwindow.h"

WorkloadWindow::WorkloadWindow(QWidget *parent, Controller* controller) :
    QWidget(parent),
    ui(new Ui::WorkloadWindow)
{
    ui->setupUi(this);
    this->controller = controller;
    this->setAperiodic_file_name(this->ui->aperiodic_filename);

    connect_sigs();
}

WorkloadWindow::~WorkloadWindow()
{
    delete ui;
}


void WorkloadWindow::connect_sigs(){
    QObject::connect(this->ui->file_input_button, &QPushButton::clicked, this->controller, &Controller::file_input_selected);
}

QPlainTextEdit *WorkloadWindow::getAperiodic_file_name() const
{
    return aperiodic_file_name;
}

void WorkloadWindow::setAperiodic_file_name(QPlainTextEdit *value)
{
    aperiodic_file_name = value;
}


