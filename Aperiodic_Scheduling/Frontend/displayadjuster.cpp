#include "displayadjuster.h"
#include "ui_displayadjuster.h"

/**
 * @brief DisplayAdjuster::DisplayAdjuster This is QWidget class. This window has a Ui file.
 * The ui holds elments that are used to set values of the GraphDisplay Widget.
 * @param parent
 */
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
