#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "QPlainTextEdit"
#include "QPushButton"
#include "Frontend/workloadwindow.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr, WorkloadWindow *workload_window = nullptr);
    void connect_sigs();

signals:

public slots:
    void file_input_selected(bool checked);


private:
    WorkloadWindow* workload_window;

};

#endif // CONTROLLER_H
