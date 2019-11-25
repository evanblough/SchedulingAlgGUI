#include "aperiodicscheduler.h"

/**
 * @brief AperiodicScheduler::AperiodicScheduler
 * This is a parent class that is implemented by PollingServer and DefferableServer.
 * This parent class serves as an interface for most aperiodic scheduling algorithims.
 */

AperiodicScheduler::AperiodicScheduler()
{

}
/**
 * @brief AperiodicScheduler::getSchedule
 * Getter Method for the schedule field
 * @return Returns a one dimensional integer array whose value maps which task
 * was run at the respective time
 * Ex: schedule[3] == 5 implies that the fifth periodic task was ran between time units 3-4
 */

int *AperiodicScheduler::getSchedule() const
{
    return schedule;
}

/**
 * @brief AperiodicScheduler::setSchedule
 * Setter Method for the schedule field.
 * @param value pointer to a schedule object
 */
void AperiodicScheduler::setSchedule(int *value)
{
    schedule = value;
}

/**
 * @brief AperiodicScheduler::getSchedule_length
 * Getter Method for schedule_length field
 * @return Returns schedule_length, which is an int that
 * represents how long the schedule will run for until it runs out
 * of tasks or enters a predictable operating state where a scheduling pattern
 * would continously repeat.
 */
int AperiodicScheduler::getSchedule_length() const
{
    return schedule_length;
}

/**
 * @brief AperiodicScheduler::setSchedule_length
 * Setter Method for schedule_length field
 * @param value
 */
void AperiodicScheduler::setSchedule_length(int value)
{
    schedule_length = value;
}
/**
 * @brief AperiodicScheduler::getScheduable
 * Getter Method for whether a task workload supplied to
 * this aperiodic scheduler was scheduable. The scheduable field
 * will be populated with a boolean value anytime a new schedule
 * is supplied to the scheduling algorithim.
 * @return Returns true if the workload passed scheduability checks and returns false
 * if it failed scheduability checks.
 */

bool AperiodicScheduler::getScheduable() const
{
    return scheduable;
}
/**
 * @brief AperiodicScheduler::setScheduable
 * Setter method for scheduable field.
 * @param value
 */
void AperiodicScheduler::setScheduable(bool value)
{
    scheduable = value;
}

int AperiodicScheduler::getNum_aper_tasks() const
{
    return num_aper_tasks;
}

void AperiodicScheduler::setNum_aper_tasks(int value)
{
    num_aper_tasks = value;
}

int AperiodicScheduler::getNum_per_tasks() const
{
    return num_per_tasks;
}

void AperiodicScheduler::setNum_per_tasks(int value)
{
    num_per_tasks = value;
}

AperiodicTask *AperiodicScheduler::getAper_tasks() const
{
    return aper_tasks;
}

void AperiodicScheduler::setAper_tasks(AperiodicTask *value)
{
    aper_tasks = value;
}

PeriodicTask *AperiodicScheduler::getPer_tasks() const
{
    return per_tasks;
}

void AperiodicScheduler::setPer_tasks(PeriodicTask *value)
{
    per_tasks = value;
}

PeriodicTask *AperiodicScheduler::getAlloted_server() const
{
    return alloted_server;
}

void AperiodicScheduler::setAlloted_server(PeriodicTask *value)
{
    alloted_server = value;
}

int AperiodicScheduler::getAlloted_server_index() const
{
    return alloted_server_index;
}

void AperiodicScheduler::setAlloted_server_index(int value)
{
    alloted_server_index = value;
}
