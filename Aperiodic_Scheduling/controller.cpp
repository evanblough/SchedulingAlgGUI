#include "controller.h"
#include "QPlainTextEdit"
#include "ui_workloadwindow.h"
#include "ui_analysiswindow.h"
#include "Frontend/workloadwindow.h"

/**
 * @brief Controller::Controller This Class is used for routing information in Frontend=>Frontend and Frontend=>Backend Communication.
 * @param parent Not used
 */
Controller::Controller(QObject *parent, WorkloadWindow* workload_window, AnalysisWindow* analysis_window) : QObject(parent)
{
    this->workload_window = workload_window;
    this->analysis_window = analysis_window;

    this->workload_set_flag = false;
    this->polling_server_flag = false;
    this->defferable_server_flag = false;
    this->cpu_flag = false;
    this->context_flag = false;
    this->response_flag = false;

    this->connect_sigs();

}


void Controller::file_input_selected(bool checked){

    //Grab Aperiodic Filename
    QString str = this->workload_window->getUi()->aperiodic_filename->toPlainText();
    QByteArray ba = str.toLocal8Bit();
    const char* file = ba.data();
    printf("Aperiodic File Input: %s\n", file);

    //Grab Periodic Filename
    str = this->workload_window->getUi()->periodic_filename->toPlainText();
    ba = str.toLocal8Bit();
    const char* file1 = ba.data();
    printf("Aperiodic File Input: %s\n", file1);

    //Todo parse files

    workload_set_flag = true;

}

void Controller::manual_input_selected(bool checked){
    //Grab Number of Aper Tasks
    QString str = this->workload_window->getUi()->num_aper_tasks->toPlainText();
    int num_aper_tasks = str.toInt();
    printf("Num of Aper Tasks: %d\n", num_aper_tasks);

    //Grab Number of Per Tasks
    str = this->workload_window->getUi()->num_per_tasks->toPlainText();
    int num_per_tasks = str.toInt();
    printf("Num of Per Tasks: %d\n", num_per_tasks);
    //Generate Manual Input Window
    //TODO

    workload_set_flag = true;

}

void Controller::polling_server_selected(bool checked){
    //If not checked set flag
    if(!defferable_server_flag){
        polling_server_flag = !polling_server_flag;
        printf("Polling Server Set\n");
    }
    //Else don't set flag and uncheck box
    else{
        this->analysis_window->getUi()->polling_server->setCheckState(Qt::CheckState::Unchecked);
    }
}

void Controller::defferable_server_selected(bool checked){
    //If not checked set flag
    if(!polling_server_flag){
        defferable_server_flag = !defferable_server_flag;
        printf("Defferable Server Set\n");
    }
    //Else don't set flag and uncheck box
    else{
        this->analysis_window->getUi()->defferable_server->setCheckState(Qt::CheckState::Unchecked);
    }
}

void Controller::cpu_selected(bool checked){
    printf("CPU Selected\n");
    cpu_flag = !cpu_flag;
}
void Controller::context_selected(bool checked){
    printf("Context Selected\n");
    context_flag = !context_flag;
}
void Controller::response_selected(bool checked){
    printf("Avg Response Selected\n");
    response_flag = !response_flag;

}



void Controller::connect_sigs(){
    //Workload Window
    //File Input Button
    QObject::connect(this->workload_window->getUi()->file_input_button, &QPushButton::clicked, this, &Controller::file_input_selected);
    //Manual Input Button
    QObject::connect(this->workload_window->getUi()->manual_input, &QPushButton::clicked, this, &Controller::manual_input_selected);

    //Analysis Window
    //Polling Server Button
    QObject::connect(this->analysis_window->getUi()->polling_server, &QCheckBox::clicked, this, &Controller::polling_server_selected);
    //Defferable Server Button
    QObject::connect(this->analysis_window->getUi()->defferable_server, &QCheckBox::clicked, this, &Controller::defferable_server_selected);
    //CPU Utilization
    QObject::connect(this->analysis_window->getUi()->cpu_utilization, &QCheckBox::clicked, this, &Controller::cpu_selected);
    //Context Switches
    QObject::connect(this->analysis_window->getUi()->num_of_switches, &QCheckBox::clicked, this, &Controller::context_selected);
    //Avg Response Time
    QObject::connect(this->analysis_window->getUi()->avg_response_time, &QCheckBox::clicked, this, &Controller::response_selected);

}


