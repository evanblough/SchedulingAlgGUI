#include "deadlinecomparator.h"

/**
 * @brief DeadlineComparator::DeadlineComparator This is a STL comparator class.
 * This comparator allows me to make a data structure in the scheduler classes that emulates
 * an earliest deadline min heap. Earliest deadline scheduling policy for aperiodic tasks
 * provides greater scheduability than FIFO.
 */

DeadlineComparator::DeadlineComparator()
{

}


int DeadlineComparator::operator()(const AperiodicTask& a1, const AperiodicTask& a2){

    return a1.getDeadline() > a2.getDeadline();
}
