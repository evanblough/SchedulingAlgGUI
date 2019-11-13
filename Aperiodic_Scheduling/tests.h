#ifndef TESTS_H
#define TESTS_H

#include <QObject>

class tests : public QObject
{
    Q_OBJECT
public:
    explicit tests(QObject *parent = nullptr);
    QString run_tests(void);

signals:

public slots:
};

#endif // TESTS_H
