#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Frontend/workloadwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, QWidget* schedule_panel = nullptr, WorkloadWindow* workload_panel = nullptr, QWidget* analysis_panel = nullptr, QWidget* display_adjuster = nullptr, QObject* controller = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void connect_sigs();
    QWidget* schedule_panel, *analysis_panel, *display_adjuster;
    WorkloadWindow* workload_panel;
    QObject* controller;
};
#endif // MAINWINDOW_H
