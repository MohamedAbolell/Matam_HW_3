#include "TaskManager.h"
using std::endl;
using std::cout;

TaskManager::TaskManager(): personCount(0) , id(0) {}

void TaskManager:: assignTask(const string &personName, const Task &task){
    if(personName == ""){
        return;
    }
    Task newTask(task.getPriority() , task.getType() , task.getDescription());
    newTask.setId(this->id);
    for(int i=0 ; i < personCount ; i++){
        if(this->persons[i].getName() == personName){
            this->persons[i].assignTask(newTask);
            id++;
            return;
        }
    }
    if(personCount == MAX_PERSONS){
        throw std::runtime_error("The system is full");
    }
    this->persons[personCount] = Person(personName);
    this->persons[personCount].assignTask(newTask);
    personCount++;
    id++;
}

void TaskManager:: completeTask(const string &personName){
    for(int i=0 ; i < personCount ; i++){
        if(this->persons[i].getName() == personName){
            this->persons[i].completeTask();
        }
    }
}