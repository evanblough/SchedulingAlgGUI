#include "backendmanualtestspollingserver.h"
#include "Backend/aperiodicscheduler.h"
#include "Backend/aperiodictask.h"
#include "Backend/periodictask.h"
#include "Backend/pollingserver.h"


BackendManualTestsPollingServer::BackendManualTestsPollingServer(QObject* parent)
{

}

bool BackendManualTestsPollingServer::results(PollingServer* ps, int len, int* sched, bool expected, int i){
    switch (i){
    default:
        return false;
    case 0:
       return ps->periodic_scheduability() == expected;
    case 1:
        return ps->aperiodic_scheduability() == expected;
    case 2:
        ps->perform_scheduability_test();
        return  ps->getScheduable() == expected;
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
void BackendManualTestsPollingServer::periodic_fail_one(){

    //Ti {ci, pi}, Ai {ri, ci, di}
    PeriodicTask per_tasks[1];
    AperiodicTask aper_tasks[3];
    //T1 = Ts {11,10};
    per_tasks[0].setComputation_time(11);
    per_tasks[0].setPeriod(10);
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


    PollingServer* ps = new PollingServer(aper_tasks, per_tasks, 3, 1, 2);
    //Input Expected values
    bool expected[3];
    //Periodic Scheduability = True
    expected[0] = false;
    //Aperiodic Scheduability = False
    expected[1] = true;
    //Scheduable = false;
    expected[2] = false;

    //Verify that each test has passed
    for(int i = 0; i < 5; i++){
        //Conver QString to const char *
        QByteArray ba = result_messages(i).toLocal8Bit();
        char* str = ba.data();
        QVERIFY2(results(ps, 0, nullptr, expected[i], i), str);
        if(!ps->getScheduable() && i == 2){
            break;
        }
    }
}
/**
 * @brief BackendManualTestsPollingServer::periodic_fail_one This test tests that an incorrect periodic task load
 * won't run
 */
void BackendManualTestsPollingServer::aperiodic_fail_one(){

    //Ti {ci, pi}, Ai {ri, ci, di}
    PeriodicTask per_tasks[1];
    AperiodicTask aper_tasks[3];
    //T1 = Ts {11,10};
    per_tasks[0].setComputation_time(3);
    per_tasks[0].setPeriod(10);
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


    PollingServer* ps = new PollingServer(aper_tasks, per_tasks, 3, 1, 2);
    //Input Expected values
    bool expected[3];
    expected[0] = true;
    expected[1] = true;
    expected[2] = true;

//    //Verify that each test has passed
//    for(int i = 0; i < 5; i++){
//        //Conver QString to const char *
//        QByteArray ba = result_messages(i).toLocal8Bit();
//        char* str = ba.data();
//        QVERIFY2(results(ps, 0, nullptr, expected[i], i), str);
//        if(!ps->getScheduable() && i == 2){
//            break;
//        }
//    }
}

void BackendManualTestsPollingServer::feasible_schedule_one(){
    PeriodicTask per_workload[3];
    AperiodicTask aper_workload[3];

    //T1 = {1,4};
    per_workload[0].setComputation_time(1);
    per_workload[0].setRemaining_cpu_time(1);
    per_workload[0].setPeriod(4);

    //T2 = {1,8};
    per_workload[1].setComputation_time(1);
    per_workload[1].setRemaining_cpu_time(1);
    per_workload[1].setPeriod(8);

    //Ts = {3, 8}
    per_workload[2].setComputation_time(3);
    per_workload[2].setRemaining_cpu_time(3);
    per_workload[2].setPeriod(8);

    //A1 = {0,2,10}
    aper_workload[0].setReady_time(0);
    aper_workload[0].setComputation_time(2);
    aper_workload[0].setRemaining_cpu_time(2);
    aper_workload[0].setDeadline(10);

    //A2 = {0,1,11}
    aper_workload[1].setReady_time(0);
    aper_workload[1].setComputation_time(1);
    aper_workload[1].setRemaining_cpu_time(1);
    aper_workload[1].setDeadline(11);

    //A3 = {0, 2, 16}
    aper_workload[2].setReady_time(0);
    aper_workload[2].setComputation_time(2);
    aper_workload[2].setRemaining_cpu_time(2);
    aper_workload[2].setDeadline(16);

    PollingServer* ps = new PollingServer(aper_workload, per_workload, 3, 3, 2);

    bool expected [3];
    expected[0] = true;
    expected[1] = true;
    expected[2] = true;

    int expected_schedule[24];
    expected_schedule[0] = 0;
    expected_schedule[1] = 1;
    expected_schedule[2] = 2;
    expected_schedule[3] = 2;
    expected_schedule[4] = 0;
    expected_schedule[5] = 2;
    expected_schedule[6] = -1;
    expected_schedule[7] = -1;
    expected_schedule[8] = 0;
    expected_schedule[9] = 1;
    expected_schedule[10] = 2;
    expected_schedule[11] = 2;
    expected_schedule[12] = 0;
    expected_schedule[13] = -1;
    expected_schedule[14] = -1;
    expected_schedule[15] = -1;
    expected_schedule[16] = 0;
    expected_schedule[17] = 1;
    expected_schedule[18] = -1;
    expected_schedule[19] = -1;
    expected_schedule[20] = 0;
    expected_schedule[21] = -1;
    expected_schedule[22] = -1;
    expected_schedule[23] = -1;

    //Verify Every Test has passed
    for(int i = 0; i < 5; i++){
        //Conver QString to const char *
        QByteArray ba = result_messages(i).toLocal8Bit();
        char* str = ba.data();
        QVERIFY2(results(ps, 24, expected_schedule, expected[i], i), str);
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


