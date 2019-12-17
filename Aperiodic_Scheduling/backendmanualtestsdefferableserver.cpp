#include "backendmanualtestsdefferableserver.h"
#include "Backend/aperiodictask.h"
#include "Backend/periodictask.h"
#include "Backend/defferableserver.h"
#include "backendmanualtestspollingserver.h"

/**
 * @brief BackendManualTestsDefferableServer::BackendManualTestsDefferableServer This test class contains tests for the DefferableServer
 * AperiodicScheduler Class.
 * @param parent
 */
BackendManualTestsDefferableServer::BackendManualTestsDefferableServer(QObject *parent) : QObject(parent)
{

}

void BackendManualTestsDefferableServer::feasible_schedule_one(){
    int num_per_tasks, num_aper_tasks, alloted_server_index;
    //Generate Workload
    PeriodicTask* per_workload = PeriodicTask::parse_file(&num_per_tasks, &alloted_server_index, "/home/rmasl/Desktop/Evan_Personal_Use/SchedulingAlgDisplay/SchedulingAlgDisplay/Aperiodic_Scheduling/InputFiles/DefferableServerTests/per_test_1.csv");
    AperiodicTask* aper_workload = AperiodicTask::parse_file(&num_aper_tasks, "/home/rmasl/Desktop/Evan_Personal_Use/SchedulingAlgDisplay/SchedulingAlgDisplay/Aperiodic_Scheduling/InputFiles/DefferableServerTests/aper_test_1.csv");
    //Generate Schedules
    int size = 0;
    int* expected_schedule = BackendManualTestsPollingServer::generate_schedule(&size, "/home/rmasl/Desktop/Evan_Personal_Use/SchedulingAlgDisplay/SchedulingAlgDisplay/Aperiodic_Scheduling/InputFiles/DefferableServerTests/result1.csv");
    DefferableServer* ds = new DefferableServer(aper_workload, per_workload, num_aper_tasks, num_per_tasks, alloted_server_index);

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
        QByteArray ba = BackendManualTestsPollingServer::result_messages(i).toLocal8Bit();
        char* str = ba.data();
        QVERIFY2(BackendManualTestsPollingServer::results(ds, size, expected_schedule, expected[i], i, finish_times), str);
        if(!ds->getScheduable() && i == 2){
            break;
        }
    }

}

void BackendManualTestsDefferableServer::feasible_schedule_two(){
    int num_per_tasks, num_aper_tasks, alloted_server_index;
    //Generate Workload
    PeriodicTask* per_workload = PeriodicTask::parse_file(&num_per_tasks, &alloted_server_index, "/home/rmasl/Desktop/Evan_Personal_Use/SchedulingAlgDisplay/SchedulingAlgDisplay/Aperiodic_Scheduling/InputFiles/DefferableServerTests/per_test_2.csv");
    AperiodicTask* aper_workload = AperiodicTask::parse_file(&num_aper_tasks, "/home/rmasl/Desktop/Evan_Personal_Use/SchedulingAlgDisplay/SchedulingAlgDisplay/Aperiodic_Scheduling/InputFiles/DefferableServerTests/aper_test_2.csv");
    //Generate Schedules
    int size = 0;
    int* expected_schedule = BackendManualTestsPollingServer::generate_schedule(&size, "/home/rmasl/Desktop/Evan_Personal_Use/SchedulingAlgDisplay/SchedulingAlgDisplay/Aperiodic_Scheduling/InputFiles/DefferableServerTests/result2.csv");
    DefferableServer* ds = new DefferableServer(aper_workload, per_workload, num_aper_tasks, num_per_tasks, alloted_server_index);

    bool expected [3];
    expected[0] = true;
    expected[1] = true;
    expected[2] = true;

    int finish_times[7];
    finish_times[0] = 7;
    finish_times[1] = 14;
    finish_times[2] = 24;
    finish_times[3] = 32;
    finish_times[4] = 35;
    finish_times[5] = 43;
    finish_times[6] = 53;

    //Verify Every Test has passed
    for(int i = 0; i < 6; i++){
        //Conver QString to const char *
        QByteArray ba = BackendManualTestsPollingServer::result_messages(i).toLocal8Bit();
        char* str = ba.data();
        QVERIFY2(BackendManualTestsPollingServer::results(ds, size, expected_schedule, expected[i], i, finish_times), str);
        if(!ds->getScheduable() && i == 2){
            break;
        }
    }
}

void BackendManualTestsDefferableServer::feasible_schedule_three(){
    int num_per_tasks, num_aper_tasks, alloted_server_index;
    //Generate Workload
    char* per_file_name = new char[4096];
    char* aper_file_name = new char[4096];
    char* result_file_name = new char[4096];

    strcpy(per_file_name, TESTFOLDER);
    strcpy(aper_file_name, TESTFOLDER);
    strcpy(result_file_name, TESTFOLDER);

    strcat(per_file_name, "per_test_3.csv");
    strcat(aper_file_name, "aper_test_3.csv");
    strcat(result_file_name, "result3.csv");
    printf("\nResultFile %s\n", result_file_name);

    PeriodicTask* per_workload = PeriodicTask::parse_file(&num_per_tasks, &alloted_server_index, per_file_name);
    AperiodicTask* aper_workload = AperiodicTask::parse_file(&num_aper_tasks, aper_file_name);

    //Generate Schedules
    int size = 0;
    int* expected_schedule = BackendManualTestsPollingServer::generate_schedule(&size, result_file_name);
    DefferableServer* ds = new DefferableServer(aper_workload, per_workload, num_aper_tasks, num_per_tasks, alloted_server_index);


    bool expected [3];
    expected[0] = true;
    expected[1] = true;
    expected[2] = true;

    int finish_times[16];
    finish_times[0] = 3;
    finish_times[1] = 5;
    finish_times[2] = 9;
    finish_times[3] = 12;
    finish_times[4] = 33;
    finish_times[5] = 37;
    finish_times[6] = 53;
    finish_times[7] = 64;
    finish_times[8] = 69;
    finish_times[9] = 90;
    finish_times[10] = 103;
    finish_times[11] = 112;
    finish_times[12] = 117;
    finish_times[13] = 125;
    finish_times[14] = 126;
    finish_times[15] = 142;

    //Verify Every Test has passed
    for(int i = 0; i < 6; i++){
        //Conver QString to const char *
        QByteArray ba = BackendManualTestsPollingServer::result_messages(i).toLocal8Bit();
        char* str = ba.data();
        QVERIFY2(BackendManualTestsPollingServer::results(ds, size, expected_schedule, expected[i], i, finish_times), str);
        if(!ds->getScheduable() && i == 2){
            break;
        }
    }
}
