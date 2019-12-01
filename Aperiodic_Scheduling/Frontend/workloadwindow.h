#ifndef WORKLOADWINDOW_H
#define WORKLOADWINDOW_H

#include <QWidget>
#include "QPlainTextEdit"
#include "QPushButton"

namespace Ui {
class WorkloadWindow;
}

class WorkloadWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WorkloadWindow(QWidget *parent = nullptr);
    ~WorkloadWindow();
    Ui::WorkloadWindow *getUi() const;


private slots:

private:
    Ui::WorkloadWindow *ui;
};

#endif // WORKLOADWINDOW_H
