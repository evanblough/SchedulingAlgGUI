#include "backendmanualtestsdefferableserver.h"
#include "Backend/aperiodictask.h"
#include "Backend/periodictask.h"
#include "Backend/defferableserver.h"
#include "backendmanualtestspollingserver.h"

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
