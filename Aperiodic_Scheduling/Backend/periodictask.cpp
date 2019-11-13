#include "periodictask.h"

/**
 * @brief PeriodicTask::PeriodicTask This class is a model for the information a periodic task would have.
 * A perioidic task can also be used to model an auxillary server that handles aperiodic tasks.
 * PollingServer and DefferableServer use a peroidic task as the model for its server.
 * @param c The number of cpu cycles the task needs to complete to finish.
 * @param p The number of cpu cycles before a new task is introduced to the system.
 */

PeriodicTask::PeriodicTask(int c, int p)
{
    this->setComputation_time(c);
    this->setRemaining_cpu_time(c);
    this->setPeriod(p);

}
/**
 * @brief PeriodicTask::getComputation_time
 * Getter Method for Computation time
 * @return
 */

int PeriodicTask::getComputation_time() const
{
    return computation_time;
}
/**
 * @brief PeriodicTask::setComputation_time
 * @param value
 */

void PeriodicTask::setComputation_time(int value)
{
    computation_time = value;
}
/**
 * @brief PeriodicTask::getPeriod
 * @return
 */

int PeriodicTask::getPeriod() const
{
    return period;
}
/**
 * @brief PeriodicTask::setPeriod
 * @param value
 */

void PeriodicTask::setPeriod(int value)
{
    period = value;
}
/**
 * @brief PeriodicTask::getRemaining_cpu_time
 * @return
 */

int PeriodicTask::getRemaining_cpu_time() const
{
    return remaining_cpu_time;
}

/**
 * @brief PeriodicTask::setRemaining_cpu_time
 * Function that sets the cpu time to a given value. This setter is used by scheduling algorihtims to refresh the remianing cpu time
 * on a task everytime it reaches its refresh period.
 * @param value
 */
void PeriodicTask::setRemaining_cpu_time(int value)
{
    remaining_cpu_time = value;
}
