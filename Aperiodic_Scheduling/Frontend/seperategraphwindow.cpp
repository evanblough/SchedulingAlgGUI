#include "seperategraphwindow.h"
#include "ui_seperategraphwindow.h"

SeperateGraphWindow::SeperateGraphWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SeperateGraphWindow)
{
    ui->setupUi(this);
}

SeperateGraphWindow::~SeperateGraphWindow()
{
    delete ui;
}

Ui::SeperateGraphWindow *SeperateGraphWindow::getUi() const
{
    return ui;
}
