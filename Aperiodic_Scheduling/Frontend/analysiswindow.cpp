#include "analysiswindow.h"
#include "ui_analysiswindow.h"

/**
 * @brief AnalysisWindow::AnalysisWindow This is a QWidget Class. It has a ui file.
 * The ui file contains ui elements that set and display parameters related to producing the schedule array.
 * @param parent
 */
AnalysisWindow::AnalysisWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalysisWindow)
{
    ui->setupUi(this);
}

AnalysisWindow::~AnalysisWindow()
{
    delete ui;
}

Ui::AnalysisWindow *AnalysisWindow::getUi() const
{
    return ui;
}
