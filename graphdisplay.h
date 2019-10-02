#ifndef GRAPHDISPLAY_H
#define GRAPHDISPLAY_H

#include <QWidget>
#include "QPainter"
#include "QPaintEvent"

class GraphDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit GraphDisplay(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

signals:

public slots:
};

#endif // GRAPHDISPLAY_H
