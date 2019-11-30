#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "QPlainTextEdit"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr, QPlainTextEdit* file_name = nullptr);
    QPlainTextEdit* file_name;

    QPlainTextEdit *getFile_name() const;
    void setFile_name(QPlainTextEdit *value);

signals:

public slots:
    void file_input_selected(bool checked);

};

#endif // CONTROLLER_H
