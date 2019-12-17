#include "analysismetrics.h"

/**
 * @brief AnalysisMetrics::AnalysisMetrics This class contains a static method for calculating perfomence metric.
 * It uses schedule arrays to determine parameters like cpu utilization, context switches, and average response time.
 */
AnalysisMetrics::AnalysisMetrics()
{

}

/**
 * @brief AnalysisMetrics::compute_metric This is the static function that is called to compute performence metrics for the schedulers.
 * @param schedule Pointer to schedule array.
 * @param schedule_length length of schedule array.
 * @param metric_id 0 for cpu utilization, 1 for context switching, 2 for average response time of aperiodic tasks.
 * @param aper_tasks AperiodicTask array, assuming the finish times are populated.
 * @param num_aper_tasks The length of the aper_tasks array.
 * @return
 */
float AnalysisMetrics::compute_metric(int* schedule, int schedule_length, int metric_id, AperiodicTask* aper_tasks, int num_aper_tasks){

    switch(metric_id){

    default:
        printf("You done goofed\n");
        break;
    //CPU Utilization Flag
    case 0:{
        int active = 0;
        //If cpu active incremenet active
        for(int i = 0; i < schedule_length; i++){
            if(schedule[i] != -1 ){
                active++;
            }
        }
        //Return active instances / total instances
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
