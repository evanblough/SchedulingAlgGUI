#include "graphdisplay.h"
#include "QPainter"
#include "QPaintEvent"

GraphDisplay::GraphDisplay(QWidget *parent, int *schedule, int sched_len, int num_tasks) : QWidget(parent)
{
    this->schedule = schedule;
    this->sched_len = sched_len;
    this->num_tasks = num_tasks;
    this->update();

}
void GraphDisplay::paintEvent(QPaintEvent *event)
{
    int width = event->rect().width() /20;
    int height = event->rect().height() /10;
    QColor task_colors[num_tasks];
    for(int i =0; i < num_tasks; i++){
        if(i % 3 == 0){
            task_colors[i] = Qt::red;
        }
        else if(i % 3 == 1){
            task_colors[i] = Qt::blue;
        }
        else{
            task_colors[i] = Qt::green;
        }

    }

    for(int i = 0; i < sched_len; i++){
            if(*(schedule + i) != -1){
                fflush(stdout);
                printf("i = %d, task number = %d \n", i, *(schedule+i));
                draw_textbox(i*width, *(schedule+i)*height, width, height, task_colors[*(schedule+i)], Qt::black, "T");
            }
    }


}
void GraphDisplay::draw_textbox(int x, int y, int width, int height, QColor background, QColor text_color, QString taskname ){
    QRect *rect = new QRect(x, y, width, height);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(text_color);
    painter.fillRect(*rect, background);
    painter.drawRect(*rect);
    painter.drawText(*rect, Qt::AlignCenter, taskname);
}
