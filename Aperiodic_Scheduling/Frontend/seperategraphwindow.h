#ifndef SEPERATEGRAPHWINDOW_H
#define SEPERATEGRAPHWINDOW_H

#include <QWidget>

namespace Ui {
class SeperateGraphWindow;
}

class SeperateGraphWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SeperateGraphWindow(QWidget *parent = nullptr);
    ~SeperateGraphWindow();

    Ui::SeperateGraphWindow *getUi() const;

private:
    Ui::SeperateGraphWindow *ui;
};

#endif // SEPERATEGRAPHWINDOW_H
