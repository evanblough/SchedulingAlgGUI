#ifndef GRAPHDISPLAY_H
#define GRAPHDISPLAY_H

#include <QWidget>
#include "QPainter"
#include "QPaintEvent"

class GraphDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit GraphDisplay(QWidget *parent = nullptr, int * schedule = nullptr, int sched_len = 0, int num_tasks = 0);
    void paintEvent(QPaintEvent *event);

signals:

public slots:
private:
    void draw_textbox(int x, int y, int width, int height, QColor background, QColor text_color, QString taskname);
    int * schedule;
    int sched_len, num_tasks;
};

#endif // GRAPHDISPLAY_H
