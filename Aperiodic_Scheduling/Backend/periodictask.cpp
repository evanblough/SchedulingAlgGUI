#include "periodictask.h"
#include <iostream>
#include <fstream>

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

PeriodicTask* PeriodicTask::parse_file(int* size, int* alloted_server_index, QString filename){
    QByteArray ba = filename.toLocal8Bit();
    const char* file = ba.data();
    printf("Periodic File Input: %s\n", file);
    std::string line;
    std::ifstream input_file (file);

    *size = 0;
    int i = 0;

    if (input_file.is_open())
      {
        if(getline(input_file,line)){
            //Set num tasks
            *size = std::stoi(line);
            PeriodicTask* workload = new PeriodicTask[*size];
        while(getline(input_file, line) && i < *size){

            int index = 0;
            QString values[2];
            values[0] = "";
            values[1] = "";
            //Iterate through line and delimit by comma
            for(unsigned j = 0; j < line.length(); j++){
                if(line.at(j) == '%'){
                    *alloted_server_index = i;
                }
                else if(line.at(j) != ','){
                     values[index].append(line.at(j));
                }
                else{
                    index++;
                }
            }
            workload[i].setComputation_time(values[0].toInt());
            workload[i].setRemaining_cpu_time(values[0].toInt());
            workload[i].setPeriod(values[1].toInt());
            i++;
        }
        input_file.close();
        return workload;

        }

    }
    input_file.close();
    return nullptr;
}
