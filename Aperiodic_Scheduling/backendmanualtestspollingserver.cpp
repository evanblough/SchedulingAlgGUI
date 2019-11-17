#include "backendmanualtestspollingserver.h"
#include "Backend/aperiodicscheduler.h"
#include "Backend/aperiodictask.h"
#include "Backend/periodictask.h"
#include "Backend/pollingserver.h"


BackendManualTestsPollingServer::BackendManualTestsPollingServer(QObject* parent)
{

}

bool BackendManualTestsPollingServer::results(PollingServer* ps, int len, int* sched, bool* expected, int i){
    switch (i){
    default:
        return false;
    case 0:
       return ps->periodic_scheduability() == expected[0];
    case 1:
        return ps->aperiodic_scheduability() == expected[1];
    case 2:
        ps->perform_scheduability_test();
        return  ps->getScheduable() == expected[2];
    case 3:
        return len == ps->getSchedule_length();
    case 4:
        int *actual_sched = ps->getSchedule();
        for(int i = 0; i < len; i++){
            if (*(sched+i) != *(actual_sched+i)){
                return false;
            }
        }
        return true;
     }

}

/**
 * @brief BackendManualTests::workload_one_test This Test supplies a
 * aperioidic workload that is not scheduable with the given periodic workload.
 * There is an aperiodic task the enters at time 0, and this task
 */
void BackendManualTestsPollingServer::workload_one_test(){

    //Ti {ci, pi}, Ai {ri, ci, di}
    PeriodicTask per_tasks[1];
    AperiodicTask aper_tasks[3];
    //T1 = Ts {3,10};
    per_tasks[0].setPeriod(10);
    per_tasks[0].setComputation_time(3);
    //A1 {0,2,10}
    aper_tasks[0].setReady_time(0);
    aper_tasks[0].setComputation_time(2);
    aper_tasks[0].setDeadline(10);
    //A2 {0,2,20}
    aper_tasks[1].setReady_time(0);
    aper_tasks[1].setComputation_time(2);
    aper_tasks[1].setDeadline(20);
    //A3 {0,2,30}
    aper_tasks[2].setReady_time(0);
    aper_tasks[2].setComputation_time(2);
    aper_tasks[2].setDeadline(30);


    PollingServer* ps = new PollingServer(aper_tasks, per_tasks, 3, 1);
    //Input Expected values
    bool expected[3];
    expected[0] = true;
    expected[1] = false;
    expected[2] = false;

    //Verify that each test has passed
    for(int i = 0; i < 5; i++){
        //Conver QString to const char *
        QByteArray ba = result_messages(i).toLocal8Bit();
        char* str = ba.data();
        QVERIFY2(results(ps, 0, nullptr, expected, i), str);
        if(!ps->getScheduable() && i == 2){
            break;
        }
    }
}
/**
 * @brief BackendManualTests::initTestCase Called before first test case. Left unpopulated because the manual unit tests
 * are just individual test cases, so they don't have a common starting point.
 */
void BackendManualTestsPollingServer::initTestCase(){
    return;
}
/**
 * @brief BackendManualTests::init Called before every test case
 */
void BackendManualTestsPollingServer::init(){
    return;
}
/**
 * @brief BackendManualTests::cleanup Called after every test case.
 */
void BackendManualTestsPollingServer::cleanup(){
    return;
}

QString BackendManualTestsPollingServer::result_messages(int i){

   switch(i){
    case 0:
        return "Periodic scheduability test differed from expected value.";
    case 1:
        return "Aperiodic scheduability test differed from expected value.";
    case 2:
        return "Scheduability test differed from expected value.";
    case 3:
        return "Schedule length varied.";
    case 4:
        return "Schedule contents varied.";
    default:
        return "Error only values of i supplied should be 0-4";

    }

}


