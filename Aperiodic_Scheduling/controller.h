#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "QPlainTextEdit"
#include "QPushButton"
#include "Frontend/workloadwindow.h"
#include "Frontend/analysiswindow.h"

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

private:
    WorkloadWindow* workload_window;
    AnalysisWindow* analysis_window;
    bool workload_set_flag, polling_server_flag, defferable_server_flag, cpu_flag, context_flag, response_flag;

};

#endif // CONTROLLER_H
