#ifndef GRAPHDISPLAY_H
#define GRAPHDISPLAY_H

#include <QWidget>
#include "QPainter"
#include "QPaintEvent"

class GraphDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit GraphDisplay(QWidget *parent = nullptr, int * schedule = nullptr, int sched_len = 0, int num_tasks = 0, int wscale = 20, int vscale = 10, int zoom = 500);
    void paintEvent(QPaintEvent *event);

    int getSched_len() const;
    void setSched_len(int value);

    int getNum_tasks() const;
    void setNum_tasks(int value);

    int getWscale() const;
    void setWscale(int value);

    int getVscale() const;
    void setVscale(int value);

    int getZoom() const;
    void setZoom(int value);

    int *getSchedule() const;
    void setSchedule(int *value);

signals:

public slots:

private:
    void draw_textbox(int x, int y, int width, int height, QColor background, QColor text_color, QString taskname);
    void draw_timeline(int box_width, int box_height, int linewidth, int width, int height, int start_time, int end_time);
    int * schedule;
    int sched_len, num_tasks, wscale, vscale, zoom;
};

#endif // GRAPHDISPLAY_H
