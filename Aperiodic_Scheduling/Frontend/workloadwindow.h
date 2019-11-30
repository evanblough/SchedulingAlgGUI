#ifndef WORKLOADWINDOW_H
#define WORKLOADWINDOW_H

#include <QWidget>
#include "controller.h"
#include "QPlainTextEdit"

namespace Ui {
class WorkloadWindow;
}

class WorkloadWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WorkloadWindow(QWidget *parent = nullptr, Controller* controller = nullptr);
    ~WorkloadWindow();

    QPlainTextEdit *getAperiodic_file_name() const;
    void setAperiodic_file_name(QPlainTextEdit *value);

private slots:

private:
    Ui::WorkloadWindow *ui;
    Controller* controller;
    void connect_sigs();
    QPlainTextEdit* aperiodic_file_name;
};

#endif // WORKLOADWINDOW_H
