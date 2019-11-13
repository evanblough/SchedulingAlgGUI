#ifndef MANUALTESTS_H
#define MANUALTESTS_H

#include <QObject>

class ManualTests
{
public:
    ManualTests();
    int frontend_tests();
    int backend_tests();
    int polling_server_tests();
    int defferable_server_tests();
    int analysis_tests();
    int task_tests();
    int system_tests();
};

#endif // MANUALTESTS_H
