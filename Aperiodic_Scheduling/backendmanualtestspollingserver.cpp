#include "backendmanualtestspollingserver.h"
#include "Backend/aperiodicscheduler.h"
#include "Backend/aperiodictask.h"
#include "Backend/periodictask.h"
#include "Backend/pollingserver.h"
#include <iostream>
#include <fstream>

BackendManualTestsPollingServer::BackendManualTestsPollingServer(QObject* parent)
{

}

bool BackendManualTestsPollingServer::results(AperiodicScheduler* ps, int len, int* sched, bool expected, int i, int* finish_times){
    switch (i){
    default:
        return false;
    case 0:
       return true;
    case 1:
        return true;
    case 2:
        return true;
    case 3:
        return len == ps->getSchedule_length();
    case 4: {
        int *actual_sched = ps->getSchedule();
        for(int i = 0; i < len; i++){
            if (*(sched+i) != *(actual_sched+i)){
                printf("\ntime: %d, Value: %d, Expected:%d\n", i, actual_sched[i], sched[i]);
                return false;
            }
        }
        return true;
    }
    case 5:
        for(int i = 0; i < ps->getNum_aper_tasks(); i++){
            if(finish_times[i] != ps->getAper_tasks()[i].getFinish_time()){
                printf("Expected: %d, Actual %d\n", finish_times[i], ps->getAper_tasks()[i].getFinish_time());
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
    expected[0] = true;
    //Aperiodic Scheduability = False
    expected[1] = true;
    //Scheduable = false;
    expected[2] = true;

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

void BackendManualTestsPollingServer::feasible_schedule_one(){

    int num_per_tasks, num_aper_tasks, alloted_server_index;
    //Generate Workload
    PeriodicTask* per_workload = PeriodicTask::parse_file(&num_per_tasks, &alloted_server_index, "/home/rmasl/Desktop/Evan_Personal_Use/SchedulingAlgDisplay/SchedulingAlgDisplay/Aperiodic_Scheduling/InputFiles/PollingServerTests/per_test_1.csv");
    AperiodicTask* aper_workload = AperiodicTask::parse_file(&num_aper_tasks, "/home/rmasl/Desktop/Evan_Personal_Use/SchedulingAlgDisplay/SchedulingAlgDisplay/Aperiodic_Scheduling/InputFiles/PollingServerTests/aper_test_1.csv");
    //Generate Schedules
    int size = 0;
    int* expected_schedule = generate_schedule(&size, "/home/rmasl/Desktop/Evan_Personal_Use/SchedulingAlgDisplay/SchedulingAlgDisplay/Aperiodic_Scheduling/InputFiles/PollingServerTests/result1.csv");
    PollingServer* ps = new PollingServer(aper_workload, per_workload, num_aper_tasks, num_per_tasks, alloted_server_index);

    bool expected [3];
    expected[0] = true;
    expected[1] = true;
    expected[2] = true;

    int finish_times[3];
    finish_times[0] = 4;
    finish_times[1] = 6;
    finish_times[2] = 12;

    //Verify Every Test has passed
    for(int i = 0; i < 6; i++){
        //Conver QString to const char *
        QByteArray ba = result_messages(i).toLocal8Bit();
        char* str = ba.data();
        QVERIFY2(results(ps, size, expected_schedule, expected[i], i, finish_times), str);
        if(!ps->getScheduable() && i == 2){
            break;
        }
    }
}

void BackendManualTestsPollingServer::feasible_schedule_two(){

    int num_per_tasks, num_aper_tasks, alloted_server_index;
    //Generate Workload
    PeriodicTask* per_workload = PeriodicTask::parse_file(&num_per_tasks, &alloted_server_index, "/home/rmasl/Desktop/Evan_Personal_Use/SchedulingAlgDisplay/SchedulingAlgDisplay/Aperiodic_Scheduling/InputFiles/PollingServerTests/per_test_2.csv");
    AperiodicTask* aper_workload = AperiodicTask::parse_file(&num_aper_tasks, "/home/rmasl/Desktop/Evan_Personal_Use/SchedulingAlgDisplay/SchedulingAlgDisplay/Aperiodic_Scheduling/InputFiles/PollingServerTests/aper_test_2.csv");
    //Generate Schedules
    int size = 0;
    int* expected_schedule = generate_schedule(&size, "/home/rmasl/Desktop/Evan_Personal_Use/SchedulingAlgDisplay/SchedulingAlgDisplay/Aperiodic_Scheduling/InputFiles/PollingServerTests/result2.csv");
    PollingServer* ps = new PollingServer(aper_workload, per_workload, num_aper_tasks, num_per_tasks, alloted_server_index);

    bool expected [3];
    expected[0] = true;
    expected[1] = true;
    expected[2] = true;

    int finish_times[7];
    finish_times[0] = 14;
    finish_times[1] = 24;
    finish_times[2] = 34;
    finish_times[3] = 42;
    finish_times[4] = 45;
    finish_times[5] = 53;
    finish_times[6] = 62;

    //Verify Every Test has passed
    for(int i = 0; i < 6; i++){
        //Conver QString to const char *
        QByteArray ba = result_messages(i).toLocal8Bit();
        char* str = ba.data();
        QVERIFY2(results(ps, size, expected_schedule, expected[i], i, finish_times), str);
        if(!ps->getScheduable() && i == 2){
            break;
        }
    }



}

void BackendManualTestsPollingServer::feasible_schedule_three(){

    int num_per_tasks, num_aper_tasks, alloted_server_index;
    //Generate Workload
    PeriodicTask* per_workload = PeriodicTask::parse_file(&num_per_tasks, &alloted_server_index, "/home/rmasl/Desktop/Evan_Personal_Use/SchedulingAlgDisplay/SchedulingAlgDisplay/Aperiodic_Scheduling/InputFiles/PollingServerTests/per_test_3.csv");
    AperiodicTask* aper_workload = AperiodicTask::parse_file(&num_aper_tasks, "/home/rmasl/Desktop/Evan_Personal_Use/SchedulingAlgDisplay/SchedulingAlgDisplay/Aperiodic_Scheduling/InputFiles/PollingServerTests/aper_test_3.csv");
    //Generate Schedules
    int size = 0;
    int* expected_schedule = generate_schedule(&size, "/home/rmasl/Desktop/Evan_Personal_Use/SchedulingAlgDisplay/SchedulingAlgDisplay/Aperiodic_Scheduling/InputFiles/PollingServerTests/result3.csv");
    PollingServer* ps = new PollingServer(aper_workload, per_workload, num_aper_tasks, num_per_tasks, alloted_server_index);

    bool expected [3];
    expected[0] = true;
    expected[1] = true;
    expected[2] = true;

    int finish_times[4];
    finish_times[0] = 19;
    finish_times[1] = 2;
    finish_times[2] = 3;
    finish_times[3] = 10;

    //Verify Every Test has passed
    for(int i = 0; i < 6; i++){
        //Conver QString to const char *
        QByteArray ba = result_messages(i).toLocal8Bit();
        char* str = ba.data();
        QVERIFY2(results(ps, size, expected_schedule, expected[i], i, finish_times), str);
        if(!ps->getScheduable() && i == 2){
            break;
        }
    }
}

void BackendManualTestsPollingServer::feasible_schedule_four(){
    int num_per_tasks, num_aper_tasks, alloted_server_index;
    //Generate Workload
    PeriodicTask* per_workload = PeriodicTask::parse_file(&num_per_tasks, &alloted_server_index, "/home/rmasl/Desktop/Evan_Personal_Use/SchedulingAlgDisplay/SchedulingAlgDisplay/Aperiodic_Scheduling/InputFiles/PollingServerTests/per_test_4.csv");
    AperiodicTask* aper_workload = AperiodicTask::parse_file(&num_aper_tasks, "/home/rmasl/Desktop/Evan_Personal_Use/SchedulingAlgDisplay/SchedulingAlgDisplay/Aperiodic_Scheduling/InputFiles/PollingServerTests/aper_test_4.csv");
    //Generate Schedules
    int size = 0;
    int* expected_schedule = generate_schedule(&size, "/home/rmasl/Desktop/Evan_Personal_Use/SchedulingAlgDisplay/SchedulingAlgDisplay/Aperiodic_Scheduling/InputFiles/PollingServerTests/result4.csv");
    PollingServer* ps = new PollingServer(aper_workload, per_workload, num_aper_tasks, num_per_tasks, alloted_server_index);

    bool expected [3];
    expected[0] = true;
    expected[1] = true;
    expected[2] = true;

    int finish_times[num_aper_tasks];
    finish_times[0] = 2;
    finish_times[1] = 3;
    finish_times[2] = 7;
    finish_times[3] = 16;
    finish_times[4] = 26;
    finish_times[5] = 31;

    //Verify Every Test has passed
    for(int i = 0; i < 6; i++){
        //Conver QString to const char *
        QByteArray ba = result_messages(i).toLocal8Bit();
        char* str = ba.data();
        QVERIFY2(results(ps, size, expected_schedule, expected[i], i, finish_times), str);
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
    case 5:
        return "Aperiodic Finish Times were not correct.";
    default:
        return "Error only values of i supplied should be 0-5";

    }

}
int* BackendManualTestsPollingServer::generate_schedule(int* size, QString filename){
    QByteArray ba = filename.toLocal8Bit();
    const char* file = ba.data();
    printf("Schedule Input: %s\n", file);
    std::string line;
    std::ifstream input_file (file);

    *size = 0;
    int i = 0;

    if(input_file.is_open()){
        if(getline(input_file, line)){
            *size = std::stoi(line);
            int* workload = new int[*size];
        while(getline(input_file, line) && i < *size){
            int index = 0;
            QString values[10];
            values[0] = "";
            values[1] = "";
            values[2] = "";
            values[3] = "";
            values[4] = "";
            values[5] = "";
            values[6] = "";
            values[7] = "";
            values[8] = "";
            values[9] = "";

            //Iterate through line and delimit by comma
            for(unsigned j = 0; j < line.length(); j++){
                if(line.at(j) != ','){
                    values[index].append(line.at(j));
                }
                else{
                    index++;
                }
            }
            for(int j = 0; j < 10; j++){
                if(!values[j].isEmpty())
                    workload[i+j] = values[j].toInt();
            }
            i = i + 10;
        }
        return workload;
        }

    }
    return nullptr;
}


