#include "controller.h"
#include "QPlainTextEdit"

/**
 * @brief Controller::Controller This Class is used for routing information in Frontend=>Frontend and Frontend=>Backend Communication.
 * @param parent Not used
 */
Controller::Controller(QObject *parent, WorkloadWindow* workload_window) : QObject(parent)
{
    this->workload_window = workload_window;
    this->connect_sigs();

}


void Controller::file_input_selected(bool checked){

    //Grab Aperiodic Filename
    QString str = this->workload_window->getAperiodic_file_name()->toPlainText();
    QByteArray ba = str.toLocal8Bit();
    const char* file = ba.data();
    printf("Aperiodic File Input: %s\n", file);

    //Grab Periodic Filename
    str = this->workload_window->getPeriodic_file_name()->toPlainText();
    ba = str.toLocal8Bit();
    const char* file1 = ba.data();
    printf("Aperiodic File Input: %s\n", file1);


}


void Controller::connect_sigs(){
    QObject::connect(this->workload_window->getFile_input_button(), &QPushButton::clicked, this, &Controller::file_input_selected);
}


