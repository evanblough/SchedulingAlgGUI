#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "QPlainTextEdit"
#include "QPushButton"
#include "Frontend/workloadwindow.h"
#include "Frontend/analysiswindow.h"
#include "Backend/aperiodictask.h"
#include "Backend/periodictask.h"
#include "Backend/aperiodicscheduler.h"
#include "Frontend/displayadjuster.h"
#include "Frontend/graphdisplay.h"


class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr, WorkloadWindow *workload_window = nullptr, AnalysisWindow* analysis_window = nullptr, DisplayAdjuster* display_adjuster = nullptr, GraphDisplay* graph_display = nullptr);
    void connect_sigs();

    void setSchedule(int *value);

signals:

public slots:
    void file_input_selected(bool checked);
    void manual_input_selected(bool checked);
    void polling_server_selected(bool checked);
    void defferable_server_selected(bool checked);
    void cpu_selected(bool checked);
    void context_selected(bool checked);
    void response_selected(bool checked);
    void run_analysis(bool checked);
    void update_zoom_level();
    void open_seperate_schedule(bool checked);
    void update_start_time();
    void update_end_time();

private:
    WorkloadWindow* workload_window;
    AnalysisWindow* analysis_window;
    DisplayAdjuster* display_adjuster;
    GraphDisplay* graph_display;
    bool workload_set_flag, polling_server_flag, defferable_server_flag, cpu_flag, context_flag, response_flag;
    int num_aper_tasks, num_per_tasks, sched_len, alloted_server_index, zoom_level, start_time, end_time;
    int* schedule;
    AperiodicTask* aper_tasks;
    PeriodicTask* per_tasks;



    bool produce_schedule(AperiodicScheduler* aper_scheduler);
    void generate_schedule_graph();

};

#endif // CONTROLLER_H
