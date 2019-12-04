#include "aperiodictask.h"
#include <iostream>
#include <fstream>


/**
 * @brief AperiodicTask::AperiodicTask
 * This class is just a data container object. This class could have maybe been replaced by a struct, but
 * it's not terribly important performence wise. This class contains the ready time, deadline, and computation time of the aperiodic task model.
 * @param r The time the aperiodic task enters the system task queue.
 * @param c The number of clock cycles a task needs to complete its computations.
 * @param d The absolute deadline that indicates when this task needs to be completed to fulfill hard real-time constraints.
 */
AperiodicTask::AperiodicTask(int r, int c, int d, int index)
{
    this->setDeadline(d);
    this->setReady_time(r);
    this->setComputation_time(c);
    this->setRemaining_cpu_time(c);
    this->setFinish_time(0);
    this->setIndex(index);
}

/**
 * @brief AperiodicTask::getComputation_time
 * Getter method for computation time.
 * @return
 */
int AperiodicTask::getComputation_time() const
{
    return computation_time;
}

/**
 * @brief AperiodicTask::setComputation_time
 * Setter Method for computation time.
 * @param value
 */
void AperiodicTask::setComputation_time(int value)
{
    computation_time = value;
}
/**
 * @brief AperiodicTask::getRemaining_cpu_time
 * Getter method for remaining_cpu_time
 * @return This returns the ammount of time a task has left to complete its computation.
 * For example, If a task has ran for 2 seconds and has a computation_time of 3, then  its remaining_cpu_time would be one.
 * This method is used by scheduling algorithim objects to keep track of remaining execution time
 */

int AperiodicTask::getRemaining_cpu_time() const
{
    return remaining_cpu_time;
}
/**
 * @brief AperiodicTask::setRemaining_cpu_time
 * Setter Method for Computation time
 * @param value
 */

void AperiodicTask::setRemaining_cpu_time(int value)
{
    remaining_cpu_time = value;
}

/**
 * @brief AperiodicTask::getDeadline
 * Getter Method for deadline. The rest of the getters and setters won't have commenting because the naming convetions are the same.
 * @return
 */
int AperiodicTask::getDeadline() const
{
    return deadline;
}

/**
 * @brief AperiodicTask::setDeadline
 * @param value
 */
void AperiodicTask::setDeadline(int value)
{
    deadline = value;
}
/**
 * @brief AperiodicTask::getReady_time
 * @return
 */

int AperiodicTask::getReady_time() const
{
    return ready_time;
}
/**
 * @brief AperiodicTask::setReady_time
 * @param value
 */
void AperiodicTask::setReady_time(int value)
{
    ready_time = value;
}
/**
 * @brief AperiodicTask::getFinish_time
 * Getter Method for Finish_time
 * @return Returns the finish_time of a task. This field is used for calculating performence metrics for aperoidic
 * schedulers like response time. Response time = finish_time - ready_time. This value is set after the schedule has been constructed.
 */

int AperiodicTask::getFinish_time() const
{
    return finish_time;
}

/**
 * @brief AperiodicTask::setFinish_time
 * @param value
 */
void AperiodicTask::setFinish_time(int value)
{
    finish_time = value;
}

int AperiodicTask::getIndex() const
{
    return index;
}

void AperiodicTask::setIndex(int value)
{
    index = value;
}

AperiodicTask* AperiodicTask::parse_file(int* size, QString filename){
    QByteArray ba = filename.toLocal8Bit();
    const char* file = ba.data();
    printf("Aperiodic File Input: %s\n", file);
    std::string line;
    std::ifstream input_file (file);
    //Todo implement Parse

    *size = 0;
    int i = 0;

    if (input_file.is_open())
      {
        if(getline(input_file,line)){
            //Set num tasks
            *size = std::stoi(line);
            AperiodicTask* workload = new AperiodicTask[*size];
        while(getline(input_file, line) && i < *size){

            workload[i].setIndex(i);
            int index = 0;
            QString values[3];
            values[0] = "";
            values[1] = "";
            values[2] = "";
            //Iterate through line and delimit by comma
            for(unsigned j = 0; j < line.length(); j++){
                if(line.at(j) != ','){
                    values[index].append(line.at(j));
                }
                else{
                    index++;
                }
            }
            //Populate Task
            workload[i].setReady_time(values[0].toInt());
            workload[i].setDeadline(values[1].toInt());
            workload[i].setComputation_time(values[2].toInt());
            workload[i].setComputation_time(values[2].toInt());
            i++;
        }
        input_file.close();
        return workload;
      }
    }
    input_file.close();
    return nullptr;

}
