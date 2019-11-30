#include "controller.h"
#include "QPlainTextEdit"

/**
 * @brief Controller::Controller This Class is used for routing information in Frontend=>Frontend and Frontend=>Backend Communication.
 * @param parent Not used.
 * @param file_name This is the textedit object held within the WorkloadWindow class. When the file input button is pressed, this textedit is
 * read from to obtain the workload input.
 */
Controller::Controller(QObject *parent, QPlainTextEdit* aperiodic_file_name) : QObject(parent)
{
    this->setAperiodic_file_name(aperiodic_file_name);

}

QPlainTextEdit *Controller::getPeriodic_file_name() const
{
    return periodic_file_name;
}

void Controller::setPeriodic_file_name(QPlainTextEdit *value)
{
    periodic_file_name = value;
}

QPlainTextEdit *Controller::getAperiodic_file_name() const
{
    return aperiodic_file_name;
}

void Controller::setAperiodic_file_name(QPlainTextEdit *value)
{
    aperiodic_file_name = value;
}


void Controller::file_input_selected(bool checked){

    //Grab Aperiodic Filename
    QString str = this->getAperiodic_file_name()->toPlainText();
    QByteArray ba = str.toLocal8Bit();
    const char* file = ba.data();
    printf("File Input: %s\n", file);
}


