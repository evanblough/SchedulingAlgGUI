#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "QPlainTextEdit"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr, QPlainTextEdit* aperiodic_file_name = nullptr);


    QPlainTextEdit *getAperiodic_file_name() const;
    void setAperiodic_file_name(QPlainTextEdit *value);

    QPlainTextEdit *getPeriodic_file_name() const;
    void setPeriodic_file_name(QPlainTextEdit *value);

signals:

public slots:
    void file_input_selected(bool checked);


private:
    QPlainTextEdit* aperiodic_file_name;
    QPlainTextEdit* periodic_file_name;

};

#endif // CONTROLLER_H
