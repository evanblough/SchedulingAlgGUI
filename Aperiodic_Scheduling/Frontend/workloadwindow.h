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

    QPlainTextEdit *getAperiodic_file_name() const;
    void setAperiodic_file_name(QPlainTextEdit *value);

    QPlainTextEdit *getPeriodic_file_name() const;
    void setPeriodic_file_name(QPlainTextEdit *value);

    QPushButton *getFile_input_button() const;
    void setFile_input_button(QPushButton *value);

    QPushButton *getManual_input_button() const;
    void setManual_input_button(QPushButton *value);

private slots:

private:
    Ui::WorkloadWindow *ui;
    QPlainTextEdit* aperiodic_file_name;
    QPlainTextEdit* periodic_file_name;
    QPushButton* file_input_button;
    QPushButton* manual_input_button;
};

#endif // WORKLOADWINDOW_H
