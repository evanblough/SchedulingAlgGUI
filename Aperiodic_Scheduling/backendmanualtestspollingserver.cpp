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
                printf("\ntime: %d, Value: %d\n", i, actual_sched[i]);
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
        //QVERIFY2(results(ps, 0, nullptr, expected[i], i), str);
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

}

void BackendManualTestsPollingServer::feasible_schedule_two(){
    PeriodicTask per_workload[4];
    AperiodicTask aper_workload[7];

    //T0 = {1,5};
    per_workload[0].setComputation_time(1);
    per_workload[0].setRemaining_cpu_time(1);
    per_workload[0].setPeriod(5);

    //TS = {4,10};
    per_workload[1].setComputation_time(4);
    per_workload[1].setRemaining_cpu_time(4);
    per_workload[1].setPeriod(10);

    //T2 = {2, 20}
    per_workload[2].setComputation_time(2);
    per_workload[2].setRemaining_cpu_time(2);
    per_workload[2].setPeriod(20);

    //T3 = {2, 50}
    per_workload[3].setComputation_time(2);
    per_workload[3].setRemaining_cpu_time(2);
    per_workload[3].setPeriod(50);

    //A0 = {3,3,20}
    aper_workload[0].setReady_time(3);
    aper_workload[0].setComputation_time(3);
    aper_workload[0].setRemaining_cpu_time(3);
    aper_workload[0].setDeadline(20);

    //A1 = {5,4,30}
    aper_workload[1].setReady_time(5);
    aper_workload[1].setComputation_time(4);
    aper_workload[1].setRemaining_cpu_time(4);
    aper_workload[1].setDeadline(30);

    //A2 = {6, 4, 40}
    aper_workload[2].setReady_time(6);
    aper_workload[2].setComputation_time(4);
    aper_workload[2].setRemaining_cpu_time(4);
    aper_workload[2].setDeadline(40);

    //A3 = {18, 2, 60}
    aper_workload[3].setReady_time(18);
    aper_workload[3].setComputation_time(2);
    aper_workload[3].setRemaining_cpu_time(2);
    aper_workload[3].setDeadline(60);

    //A4 = {25, 3, 75}
    aper_workload[4].setReady_time(25);
    aper_workload[4].setComputation_time(3);
    aper_workload[4].setRemaining_cpu_time(3);
    aper_workload[4].setDeadline(75);

    //A5 = {32, 2, 87}
    aper_workload[5].setReady_time(32);
    aper_workload[5].setComputation_time(2);
    aper_workload[5].setRemaining_cpu_time(2);
    aper_workload[5].setDeadline(87);

    //A6 = {49, 3, 95}
    aper_workload[6].setReady_time(49);
    aper_workload[6].setComputation_time(3);
    aper_workload[6].setRemaining_cpu_time(3);
    aper_workload[6].setDeadline(95);

    PollingServer* ps = new PollingServer(aper_workload, per_workload, 7, 4, 1);

    bool expected [3];
    expected[0] = true;
    expected[1] = true;
    expected[2] = true;

    int expected_schedule[100];
    expected_schedule[0] = 0;
    expected_schedule[1] = 2;
    expected_schedule[2] = 2;
    expected_schedule[3] = 3;
    expected_schedule[4] = 3;
    expected_schedule[5] = 0;
    expected_schedule[6] = -1;
    expected_schedule[7] = -1;
    expected_schedule[8] = -1;
    expected_schedule[9] = -1;
    expected_schedule[10] = 0;
    expected_schedule[11] = 1;
    expected_schedule[12] = 1;
    expected_schedule[13] = 1;
    expected_schedule[14] = 1;
    expected_schedule[15] = 0;
    expected_schedule[16] = -1;
    expected_schedule[17] = -1;
    expected_schedule[18] = -1;
    expected_schedule[19] = -1;
    expected_schedule[20] = 0;
    expected_schedule[21] = 1;
    expected_schedule[22] = 1;
    expected_schedule[23] = 1;
    expected_schedule[24] = 1;
    expected_schedule[25] = 0;
    expected_schedule[26] = 2;
    expected_schedule[27] = 2;
    expected_schedule[28] = -1;
    expected_schedule[29] = -1;
    expected_schedule[30] = 0;
    expected_schedule[31] = 1;
    expected_schedule[32] = 1;
    expected_schedule[33] = 1;
    expected_schedule[34] = 1;
    expected_schedule[35] = 0;
    expected_schedule[36] = -1;
    expected_schedule[37] = -1;
    expected_schedule[38] = -1;
    expected_schedule[39] = -1;
    expected_schedule[40] = 0;
    expected_schedule[41] = 1;
    expected_schedule[42] = 1;
    expected_schedule[43] = 1;
    expected_schedule[44] = 1;
    expected_schedule[45] = 0;
    expected_schedule[46] = 2;
    expected_schedule[47] = 2;
    expected_schedule[48] = -1;
    expected_schedule[49] = -1;
    expected_schedule[50] = 0;
    expected_schedule[51] = 1;
    expected_schedule[52] = 1;
    expected_schedule[53] = 1;
    expected_schedule[54] = 1;
    expected_schedule[55] = 0;
    expected_schedule[56] = 3;
    expected_schedule[57] = 3;
    expected_schedule[58] = -1;
    expected_schedule[59] = -1;
    expected_schedule[60] = 0;
    expected_schedule[61] = 1;
    expected_schedule[62] = 2;
    expected_schedule[63] = 2;
    expected_schedule[64] = -1;
    expected_schedule[65] = 0;
    expected_schedule[66] = -1;
    expected_schedule[67] = -1;
    expected_schedule[68] = -1;
    expected_schedule[69] = -1;
    expected_schedule[70] = 0;
    expected_schedule[71] = -1;
    expected_schedule[72] = -1;
    expected_schedule[73] = -1;
    expected_schedule[74] = -1;
    expected_schedule[75] = 0;
    expected_schedule[76] = -1;
    expected_schedule[77] = -1;
    expected_schedule[78] = -1;
    expected_schedule[79] = -1;
    expected_schedule[80] = 0;
    expected_schedule[81] = 2;
    expected_schedule[82] = 2;
    expected_schedule[83] = -1;
    expected_schedule[84] = -1;
    expected_schedule[85] = 0;
    expected_schedule[86] = -1;
    expected_schedule[87] = -1;
    expected_schedule[88] = -1;
    expected_schedule[89] = -1;
    expected_schedule[90] = 0;
    expected_schedule[91] = -1;
    expected_schedule[92] = -1;
    expected_schedule[93] = -1;
    expected_schedule[94] = -1;
    expected_schedule[95] = 0;
    expected_schedule[96] = -1;
    expected_schedule[97] = -1;
    expected_schedule[98] = -1;
    expected_schedule[99] = -1;



    //Verify Every Test has passed
    for(int i = 0; i < 5; i++){
        //Conver QString to const char *
        QByteArray ba = result_messages(i).toLocal8Bit();
        char* str = ba.data();
        QVERIFY2(results(ps, 100, expected_schedule, expected[i], i), str);
        if(!ps->getScheduable() && i == 2){
            break;
        }
    }



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

    //God forgive me for this
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


