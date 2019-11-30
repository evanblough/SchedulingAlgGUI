#ifndef WORKLOADWINDOW_H
#define WORKLOADWINDOW_H

#include <QWidget>

namespace Ui {
class WorkloadWindow;
}

class WorkloadWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WorkloadWindow(QWidget *parent = nullptr);
    ~WorkloadWindow();

private slots:
    void on_verticalScrollBar_sliderMoved(int position);

    void on_verticalScrollBar_valueChanged(int value);

private:
    Ui::WorkloadWindow *ui;
};

#endif // WORKLOADWINDOW_H
