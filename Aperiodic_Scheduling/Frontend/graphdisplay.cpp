#include "graphdisplay.h"
#include "QPainter"
#include "QPaintEvent"

GraphDisplay::GraphDisplay(QWidget *parent, int *schedule, int sched_len, int num_tasks, int wscale, int vscale) : QWidget(parent)
{
    this->schedule = schedule;
    this->sched_len = sched_len;
    this->num_tasks = num_tasks;
    this->wscale = wscale;
    this->vscale = vscale;
    this->update();

}

//Called everytime a paintevent triggered ex: resize screen etc.
void GraphDisplay::paintEvent(QPaintEvent *event)
{

    int width = event->rect().width() /wscale;
    int height = event->rect().height() / vscale ;

    //Assign Colors to tasks
    QColor task_colors[num_tasks];
    for(int i =0; i < num_tasks; i++){
        if(i % 4 == 0){
            //Light Blue
            task_colors[i].setNamedColor("#BFFBFF");
        }
        else if(i % 4 == 1){
            //Teal
            task_colors[i].setNamedColor("#1FCBFF");
        }
        else if (i % 4 == 2){
            //Carolina Blue
            task_colors[i].setNamedColor("#2B95FF");
        }
        else{
            //Dark Blue
            task_colors[i].setNamedColor("#3414FF");
        }

    }
    //Shouldn't have more than 10^50 tasks
    char task_name[50];
    //Iterate through schedule and paint boxes in relative coordinates
    for(int i = 0; i < sched_len; i++){
            if(*(schedule + i) != -1){
                sprintf(task_name, "T%d", *(schedule+i));
                draw_textbox(i*width, *(schedule+i)*height, width, height, task_colors[*(schedule+i)], Qt::black, task_name);
            }
    }
    //Create Timeline
    draw_timeline(event->rect().width(), event->rect().height(), 1, width, height, 0, sched_len);


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

void GraphDisplay::draw_timeline(int box_width, int box_height, int linewidth, int width, int height, int start_time, int end_time){

    QPainter painter(this);
    char index[end_time - start_time];
    //Draw Horizontal Line
    painter.setPen(*new QColor("#e4edf5"));
    painter.drawLine(0, box_height -1, box_width, box_height-1);
    painter.drawLine(0, 0, box_width, 0);
    painter.drawLine(box_width - 1, 0, box_width - 1, box_height);
    painter.drawLine(0, box_height - height/2, box_width, box_height - height/2);

    //Draw Hashes
    for(int i = 0; i < box_width/width; i++){
        painter.drawLine(i*width, 0, i*width, box_height);
        sprintf(index, "%d", start_time + i);
        painter.drawText(i*width + 5, box_height - height/4, index);
    }





}
