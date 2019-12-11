#include "analysismetrics.h"

AnalysisMetrics::AnalysisMetrics()
{

}

float AnalysisMetrics::compute_metric(int* schedule, int schedule_length, int metric_id, AperiodicTask* aper_tasks, int num_aper_tasks){

    switch(metric_id){

    default:
        printf("You done goofed\n");
        break;
    //CPU Utilization Flag
    case 0:{
        int active = 0;
        for(int i = 0; i < schedule_length; i++){
            if(schedule[i] != -1 ){
                active++;
            }
        }
        return float(active)/float(schedule_length);
    }
    //Context Switch
    case 1:{
        int context_switches = 0;
        int last_run_task = schedule[0];
        for(int i = 0; i < schedule_length; i++){
            if(schedule[i] != last_run_task){
                context_switches++;
            }
            last_run_task = schedule[i];
        }
        return context_switches;

    }
    //Avg Response
    case 2:{
        float sum = 0.000;
        for(int i = 0; i < num_aper_tasks; i++){
            sum += aper_tasks[i].getFinish_time() - aper_tasks[i].getReady_time();
        }
        return sum/num_aper_tasks;

    }

    }
    return 0.000;

}
