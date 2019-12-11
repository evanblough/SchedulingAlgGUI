#include "controller.h"
#include "QPlainTextEdit"
#include "ui_workloadwindow.h"
#include "ui_analysiswindow.h"
#include "Frontend/workloadwindow.h"
#include "Backend/defferableserver.h"
#include "Backend/pollingserver.h"
#include "ui_displayadjuster.h"
#include "Backend/analysismetrics.h"

/**
 * @brief Controller::Controller This Class is used for routing information in Frontend=>Frontend and Frontend=>Backend Communication.
 * @param parent Not used
 */
Controller::Controller(QObject *parent, WorkloadWindow* workload_window, AnalysisWindow* analysis_window, DisplayAdjuster* display_adjuster, GraphDisplay* graph_display) : QObject(parent)
{
    this->workload_window = workload_window;
    this->analysis_window = analysis_window;
    this->display_adjuster = display_adjuster;
    this->graph_display = graph_display;

    this->workload_set_flag = false;
    this->polling_server_flag = false;
    this->defferable_server_flag = false;
    this->cpu_flag = false;
    this->context_flag = false;
    this->response_flag = false;

    this->zoom_level = 20;
    schedule = nullptr;
    this->alloted_server_index = 0;

    this->connect_sigs();

}


void Controller::file_input_selected(bool checked){

    //Grab Aperiodic Filename
    QString str = this->workload_window->getUi()->aperiodic_filename->toPlainText();
    QByteArray ba = str.toLocal8Bit();
    const char* file = ba.data();
    printf("Aperiodic File Input: %s\n", file);

    aper_tasks = AperiodicTask::parse_file(&this->num_aper_tasks, str);
    for(int i =0; i< num_aper_tasks; i++){
        fflush(stdout);
        printf("Aper Stats %d: %d, %d, %d\n", aper_tasks[i].getIndex(), aper_tasks[i].getReady_time(), aper_tasks[i].getComputation_time(), aper_tasks[i].getDeadline());
    }

    //Grab Periodic Filename
    str = this->workload_window->getUi()->periodic_filename->toPlainText();
    ba = str.toLocal8Bit();
    const char* file1 = ba.data();
    printf("Periodic File Input: %s\n", file1);

    per_tasks = PeriodicTask::parse_file(&this->num_per_tasks, &this->alloted_server_index, str);
    for(int i =0; i< num_per_tasks; i++){
        fflush(stdout);
        printf("Per Stats %d: %d, %d, %d\n", i, per_tasks[i].getComputation_time(), per_tasks[i].getPeriod(), alloted_server_index);
    }


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
void Controller::run_analysis(bool checked){
    //Run compatibility checks
    if(!defferable_server_flag && !polling_server_flag){
        printf("Invalid run configuration: Select either defferable server or polling server\n");
        return;
    }
    if(!workload_set_flag){
        printf("Invalid Run Configuration: Provide a workload input");
        return;
    }
    //Attempt to generate Scheduler Object
    if(defferable_server_flag){
        DefferableServer* ds = new DefferableServer(aper_tasks, per_tasks, num_aper_tasks, num_per_tasks, alloted_server_index);
        if(produce_schedule(ds))
            generate_schedule_graph();
        else
            printf("Workload not scheduable under Defferable Server\n");
    }
    else{
        PollingServer* ps = new PollingServer(aper_tasks, per_tasks, num_aper_tasks, num_per_tasks, alloted_server_index);
        if(produce_schedule(ps))
            generate_schedule_graph();
        else
            printf("Workload not scheduable under Polling Server");
    }
    //CPU Utiliztion
    if(cpu_flag){
        QString cpu_utilization = QString::number(AnalysisMetrics::compute_metric(schedule, sched_len, 0, aper_tasks, num_aper_tasks));
        analysis_window->getUi()->cpu_output->setPlainText(cpu_utilization);
    }
    //Context Switches
    if(context_flag){
        QString context = QString::number(AnalysisMetrics::compute_metric(schedule, sched_len, 1, aper_tasks, num_aper_tasks));
        analysis_window->getUi()->switch_output->setPlainText(context);
    }
    //Average Response Time
    if(response_flag){
        QString response = QString::number(AnalysisMetrics::compute_metric(schedule, sched_len, 2, aper_tasks, num_aper_tasks));
        analysis_window->getUi()->resp_time_output->setPlainText(response);
    }

}

bool Controller::produce_schedule(AperiodicScheduler* aper_scheduler){
    schedule = aper_scheduler->getSchedule();
    sched_len = aper_scheduler->getSchedule_length();
    aper_tasks = aper_scheduler->getAper_tasks();
    per_tasks = aper_scheduler->getPer_tasks();
    return aper_scheduler->getScheduable();
}

void Controller::generate_schedule_graph(){
    graph_display->setNum_tasks(this->num_per_tasks);
    graph_display->setSched_len(sched_len);
    graph_display->setSchedule(schedule);
    graph_display->setFixedSize(30000, 500);
    graph_display->setW(30000);
    graph_display->setH(500);
    graph_display->setVscale(this->num_per_tasks+1);
    graph_display->setWscale(this->sched_len);
    graph_display->update();
    return;
}

void Controller::update_zoom_level(){
    QString text = this->display_adjuster->getUi()->zoom_level->toPlainText();
    this->zoom_level = text.toInt();
    if(zoom_level <= 0)
        zoom_level = 20;
    printf("Zoomy: %d\n", this->zoom_level);
    graph_display->setZoom(zoom_level);
    graph_display->update();
}

void Controller::open_seperate_schedule(bool checked){
//TODO
    printf("Open Seperate Schedule\n");
}

void Controller::update_start_time(){
    start_time = this->display_adjuster->getUi()->start_time->toPlainText().toInt();
    //Fix Invalid Input
    if(start_time < 0 || start_time > end_time){
        start_time = 0;
        this->display_adjuster->getUi()->start_time->clear();
    }

}

void Controller::update_end_time(){
    //TODO: Add CASES to check if start and end are populated;
    end_time = this->display_adjuster->getUi()->end_time->toPlainText().toInt();
    //Fix Invalid Input
    if(end_time < 1 || end_time <= start_time){
        end_time = this->sched_len;
        this->display_adjuster->getUi()->end_time->clear();
    }
    if(end_time < 1 || end_time <= start_time){
        end_time = 0;if(end_time < 1 || end_time <= start_time){
            end_time = this->sched_len;
        }
    }


}

void Controller::setSchedule(int *value)
{
    schedule = value;
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
    //Run Analysis Button
    QObject::connect(this->analysis_window->getUi()->run_analysis, &QPushButton::clicked, this, &Controller::run_analysis);

    //Display Adjuster Window
    //Zoom Level
    QObject::connect(this->display_adjuster->getUi()->zoom_level, &QPlainTextEdit::textChanged, this, &Controller::update_zoom_level);
    //Open New Display Window
    QObject::connect(this->display_adjuster->getUi()->open_seperate_window, &QPushButton::clicked, this, &Controller::open_seperate_schedule);
    //Start Time
    QObject::connect(this->display_adjuster->getUi()->start_time, &QPlainTextEdit::textChanged, this, &Controller::update_start_time);
    //End Time
    QObject::connect(this->display_adjuster->getUi()->end_time, &QPlainTextEdit::textChanged, this, &Controller::update_end_time);

}


