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
