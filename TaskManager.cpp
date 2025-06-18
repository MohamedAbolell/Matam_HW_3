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
// not finished
void TaskManager:: bumpPriorityByType(TaskType type, int priority){
    if(priority < 0){
        return;
    }
    SortedList<Task> newList;
    for(int i=0 ; i < personCount ; i++){
        newList = this->persons[i].getTasks().apply(
                [type,priority](const Task& task)->Task{
                    if(task.getType() == type){
                        Task newTask(task.getPriority()+priority , task.getType() , task.getDescription());
                        newTask.setId(task.getId());
                        return newTask;
                    }
                    return task;
                });
        this->persons[i].setTasks(newList);
    }
}
void TaskManager:: printAllEmployees() const{
    for(int i=0 ; i < personCount ; i++){
        cout << this->persons[i] << endl;
    }
}
void TaskManager:: printAllTasks() const{
    SortedList<Task> printList;
    for(int i=0 ; i < personCount ; i++){
        for(const Task& task: this->persons[i].getTasks()){
            printList.insert(task);
        }
    }
    for(const Task& task: printList){
        cout << task << endl;
    }
}
void TaskManager:: printTasksByType(TaskType type) const{
    SortedList<Task> comb;
    for(int i=0 ; i < personCount ; i++){
        for(const Task& task: this->persons[i].getTasks()){
            comb.insert(task);
        }
    }
    SortedList<Task> printList =comb.filter([type](const Task& task){return task.getType() == type;});
    for(const Task& task: printList){
        cout << task << endl;
    }
}
