#include "controller.h"
#include "QPlainTextEdit"

Controller::Controller(QObject *parent, QPlainTextEdit* file_name) : QObject(parent)
{
    this->setFile_name(file_name);

}

QPlainTextEdit *Controller::getFile_name() const
{
    return file_name;
}

void Controller::setFile_name(QPlainTextEdit *value)
{
    file_name = value;
}

void Controller::file_input_selected(bool checked){

    QString str = this->getFile_name()->toPlainText();
    QByteArray ba = str.toLocal8Bit();
    const char* file = ba.data();
    printf("File Input: %s\n", file);
}


