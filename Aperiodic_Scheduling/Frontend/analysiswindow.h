#ifndef ANALYSISWINDOW_H
#define ANALYSISWINDOW_H

#include <QWidget>

namespace Ui {
class AnalysisWindow;
}

class AnalysisWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AnalysisWindow(QWidget *parent = nullptr);
    ~AnalysisWindow();

    Ui::AnalysisWindow *getUi() const;

private:
    Ui::AnalysisWindow *ui;
};

#endif // ANALYSISWINDOW_H
