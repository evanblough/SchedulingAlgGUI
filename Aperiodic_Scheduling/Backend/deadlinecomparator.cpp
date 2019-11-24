#include "deadlinecomparator.h"

DeadlineComparator::DeadlineComparator()
{

}


int DeadlineComparator::operator()(const AperiodicTask& a1, const AperiodicTask& a2){

    return a1.getDeadline() > a2.getDeadline();
}
