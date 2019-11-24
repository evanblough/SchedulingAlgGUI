#ifndef DEADLINECOMPARATOR_H
#define DEADLINECOMPARATOR_H
#include "Backend/aperiodictask.h"


class DeadlineComparator
{
public:
    DeadlineComparator();
    int operator() (const AperiodicTask& a1, const AperiodicTask& a2);
};

#endif // DEADLINECOMPARATOR_H
