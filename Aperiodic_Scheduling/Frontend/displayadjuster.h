#ifndef DISPLAYADJUSTER_H
#define DISPLAYADJUSTER_H

#include <QWidget>

namespace Ui {
class DisplayAdjuster;
}

class DisplayAdjuster : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayAdjuster(QWidget *parent = nullptr);
    ~DisplayAdjuster();

private:
    Ui::DisplayAdjuster *ui;
};

#endif // DISPLAYADJUSTER_H
