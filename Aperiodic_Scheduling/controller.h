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

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr, WorkloadWindow *workload_window = nullptr, AnalysisWindow* analysis_window = nullptr);
    void connect_sigs();

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

private:
    WorkloadWindow* workload_window;
    AnalysisWindow* analysis_window;
    bool workload_set_flag, polling_server_flag, defferable_server_flag, cpu_flag, context_flag, response_flag;
    int num_aper_tasks, num_per_tasks, sched_len, alloted_server_index;
    int* schedule;
    AperiodicTask* aper_tasks;
    PeriodicTask* per_tasks;

    bool produce_schedule(AperiodicScheduler* aper_scheduler);
    void generate_schedule_graph();

};

#endif // CONTROLLER_H
