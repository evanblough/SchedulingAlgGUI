#ifndef ANALYSISMETRICS_H
#define ANALYSISMETRICS_H

#include <QObject>
#include "Backend/aperiodictask.h"

class AnalysisMetrics
{
public:
    AnalysisMetrics();
    static float compute_metric(int* schedule, int schedule_length, int metric_id, AperiodicTask* aper_tasks, int aperiodic_tasks);
};

#endif // ANALYSISMETRICS_H
