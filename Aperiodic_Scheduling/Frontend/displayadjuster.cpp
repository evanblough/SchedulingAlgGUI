#include "displayadjuster.h"
#include "ui_displayadjuster.h"

DisplayAdjuster::DisplayAdjuster(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayAdjuster)
{
    ui->setupUi(this);
}

DisplayAdjuster::~DisplayAdjuster()
{
    delete ui;
}

Ui::DisplayAdjuster *DisplayAdjuster::getUi() const
{
    return ui;
}
