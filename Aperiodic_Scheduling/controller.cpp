#include "controller.h"
#include "QPlainTextEdit"
#include "ui_workloadwindow.h"
#include "ui_analysiswindow.h"
#include "Frontend/workloadwindow.h"
#include "Backend/defferableserver.h"
#include "Backend/pollingserver.h"
#include "ui_displayadjuster.h"
#include "Backend/analysismetrics.h"
#include "ui_seperategraphwindow.h"
#include "Frontend/seperategraphwindow.h"

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

/**
 * @brief Controller::file_input_selected This is a slot that is mapped to the file input button. This will execute upon pressing the file input button.
 * It will try to read from the files currently in the input window.
 * @param checked
 */
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
/**
 * @brief Controller::manual_input_selected This slot will launch a manual output subwindow based on the number of tasks inputted by the user.
 * It is triggered by the manual input button in the mainwindow
 * @param checked
 */
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
/**
 * @brief Controller::polling_server_selected This is a slot mapped to the pollingserver checkbox in the analysis window. When the polling server box is checked it will
 * lock the field until run_analysis button or polling server is unclicked.
 * @param checked
 */
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

/**
 * @brief Controller::defferable_server_selected This is another slot with the same function as polling_server_selected(), except for defferable server.
 * @param checked
 */
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

/**
 * @brief Controller::cpu_selected This is a slot that is mapped to the cpu checkbox in the AnalysisWindow class.
 * @param checked
 */
void Controller::cpu_selected(bool checked){
    printf("CPU Selected\n");
    cpu_flag = !cpu_flag;
}
/**
 * @brief Controller::context_selected This is a slot that is mapped to the context switch checkbox in the AnalysisWindow class.
 * @param checked
 */
void Controller::context_selected(bool checked){
    printf("Context Selected\n");
    context_flag = !context_flag;
}

/**
 * @brief Controller::response_selected This is a slot that is mapped to the avg response time checkbox in the AnalysisWindow class.
 * @param checked
 */
void Controller::response_selected(bool checked){
    printf("Avg Response Selected\n");
    response_flag = !response_flag;

}
/**
 * @brief Controller::run_analysis This is a slot that is mapped to the run analysis button in the AnalysisWindow.
 * It will check all the flags of the controller class to check for a valid run configuration.
 * If the run configuration is valid it will generate an AperiodicScheduler object and populate the graph display window at the top of the mainwindow.
 * It will also compute any checked analysis metrics
 * @param checked
 */
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

/**
 * @brief Controller::produce_schedule This function is called by the run_analysis() slot. It generates a schedule array for to fill the schedule field of the controller class.
 * @param aper_scheduler this is the scheduler that will produce the schedule. It could be polling server or defferable server.
 * @return Returns a pointer to the schedule array.
 */
bool Controller::produce_schedule(AperiodicScheduler* aper_scheduler){
    schedule = aper_scheduler->getSchedule();
    sched_len = aper_scheduler->getSchedule_length();
    aper_tasks = aper_scheduler->getAper_tasks();
    per_tasks = aper_scheduler->getPer_tasks();
    return aper_scheduler->getScheduable();
}

/**
 * @brief Controller::generate_schedule_graph This function is called by run_analysis() to fill the fields in GraphDisplay object to
 * display the graph. It automatically scales it to an even size.
 */
void Controller::generate_schedule_graph(){
    graph_display->setNum_tasks(this->num_per_tasks);
    graph_display->setSched_len(sched_len);
    graph_display->setSchedule(schedule);
    graph_display->setFixedSize(this->sched_len*30, this->num_per_tasks*80);
    graph_display->setW(this->sched_len*30);
    graph_display->setH(this->num_per_tasks*80);
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

/**
 * @brief Controller::open_seperate_schedule This slot is mapped to the open_seperate_window button of the DisplayAdjuster Window.
 * This opens a seperate graph display window, because it is hard to view sometimes with large schedules.
 * @param checked
 */
void Controller::open_seperate_schedule(bool checked){

    printf("Open Seperate Schedule\n");
    GraphDisplay* gd = new GraphDisplay();
    gd->setNum_tasks(this->num_per_tasks);
    gd->setSched_len(sched_len);
    gd->setSchedule(schedule);
    gd->setFixedSize(this->sched_len*30, this->num_per_tasks*80);
    gd->setW(this->sched_len*30);
    gd->setH(this->num_per_tasks*80);
    gd->setVscale(this->num_per_tasks+1);
    gd->setWscale(this->sched_len);
    gd->update();

    QColor colors[7];
    colors[0].setNamedColor("#BFFBFF"); //Pale Blue
    colors[1].setNamedColor("#1FCBFF"); //Teal
    colors[2].setNamedColor("#2B95FF"); //Carolina Blue
    colors[3].setNamedColor("#3414FF"); //Blue
    colors[4].setNamedColor("#7A05FF"); //Purp
    colors[5].setNamedColor("#065951"); //Dark Teal
    colors[6].setNamedColor("#292629"); //Dark Grey

    QPalette* palette = new QPalette(colors[1], colors[6], colors[0], colors[5], colors[2], colors[0], colors[6]);

    SeperateGraphWindow* gw = new SeperateGraphWindow();
    gw->setPalette(*palette);
    gw->getUi()->scrollArea->setWidget(gd);
    gd->show();
    gw->show();
    return;

}

/**
 * @brief Controller::update_start_time This sets the left bound for the GraphDisplay Window.
 */
void Controller::update_start_time(){
    start_time = this->display_adjuster->getUi()->start_time->toPlainText().toInt();
    //Fix Invalid Input
    if(start_time < 0 || start_time > end_time){
        start_time = 0;
        this->display_adjuster->getUi()->start_time->clear();
    }

}

/**
 * @brief Controller::update_end_time This slot sets the right bound for the GraphDisplay Window.
 */
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


/**
 * @brief Controller::connect_sigs This function is called in the constructor to
 * Map all the slots and signals of the subwindows of the mainwindow.
 */
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


