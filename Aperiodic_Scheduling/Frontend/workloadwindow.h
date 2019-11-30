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

    Ui::WorkloadWindow *getUi() const;
    void setUi(Ui::WorkloadWindow *value);

    QPlainTextEdit *getFile_name() const;
    void setFile_name(QPlainTextEdit *value);

private slots:
    void on_verticalScrollBar_sliderMoved(int position);
    void on_verticalScrollBar_valueChanged(int value);

private:
    Ui::WorkloadWindow *ui;
    Controller* controller;
    void connect_sigs();
    QPlainTextEdit* file_name;
};

#endif // WORKLOADWINDOW_H
