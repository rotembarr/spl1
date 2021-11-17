#include "Action.h"
#include "Studio.h"

using namespace std;

Studio studio_backup;

//  Base Action

BaseAction::BaseAction(){
    this->errorMsg = "";
}
ActionStatus BaseAction::getStatus() const {
    return this->status;
}
void BaseAction::complete(){
    this->status = COMPLETED;
}
void BaseAction::error(std::string errorMsg){
    this->status = ERROR;
    this->errorMsg = errorMsg;
}
std::string BaseAction::getErrorMsg() const{
    return "Error: " + this->errorMsg;
}


//  Open Trainer
OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList): trainerId(id), customers(customersList) {}
void OpenTrainer::act(Studio &studio){
    Trainer* trainer = studio.getTrainer(this->trainerId);

    if(trainer == nullptr){
        this->error("Workout session does not exist or is already open");
        return;
    }

    if(trainer->isOpen()){
        this->error("Workout session does not exist or is already open");
        return;
    }

    for(size_t i = 0; i < this->customers.size(); i++){
        trainer->addCustomer(this->customers[i]);
    }

    trainer->openTrainer();
}
std::string OpenTrainer::toString() const{
    string result = "";
    result += "open " + to_string(this->trainerId) + " ";
    for(size_t i = 0; i < this->customers.size(); i++){
        result += this->customers[i]->getName() + "," + this->customers[i]->customer_type();
    }
    result += " ";
    if(this->getStatus() == COMPLETED){
        result += "Completed";
    } else {
        result += this->getErrorMsg();
    }
    return result;
}


//  Order
Order::Order(int id): trainerId(id) {}
void Order::act(Studio &studio){
    Trainer* trainer = studio.getTrainer(this->trainerId);

    //  No trainer exists
    if(trainer == nullptr){
        this->error("Trainer does not exist or is not open");
        return;
    }

    //  Trainer is closed
    if (!trainer->isOpen()){
        this->error("Trainer does not exist or is not open");
        return;
    }

    //  Start the trainers order
    std::vector<Customer*> customer_list = trainer->getCustomers();
    for(size_t i = 0; i < customer_list.size(); i++){
        trainer->order(customer_list[i]->getId(), customer_list[i]->order(studio.getWorkoutOptions()), studio.getWorkoutOptions());
    }
    this->complete();
}
std::string Order::toString() const{
    string result = "";
    result += "order " + to_string(this->trainerId) + " ";
    if(this->getStatus() == COMPLETED){
        result += "Completed";
    } else {
        result += this->getErrorMsg();
    }
    return result;
}

//  Move customer
MoveCustomer::MoveCustomer(int src, int dst, int customerId): srcTrainer(src), dstTrainer(dst), id(customerId) {}
void MoveCustomer::act(Studio &studio){

    //  Get trainers and customer.
    Trainer* srcTrainer_p = studio.getTrainer(this->srcTrainer);
    Trainer* dstTrainer_p = studio.getTrainer(this->dstTrainer);
    Customer* customer_p = srcTrainer_p->getCustomer(this->id);


    //  No trainer / customer exists
    if((srcTrainer_p == nullptr) | (dstTrainer_p == nullptr) | (customer_p == nullptr)){
        this->error("Cannot move costumer");
        return;
    }

    //  Either trainer is closed
    if((!srcTrainer_p->isOpen()) | (!dstTrainer_p->isOpen())){
        this->error("Cannot move costumer");
        return;
    }

    //  Customer is not under src Trainer
    if(srcTrainer_p->getCustomer(this->id) == nullptr){
        this->error("Cannot move costumer");
        return;
    }

    //  No capacity in dst Trainer for customers workout.
    if(dstTrainer_p->getCapacity() - dstTrainer_p->getOrders().size() < customer_p->order(studio.getWorkoutOptions()).size()){
        this->error("Cannot move costumer");
        return;
    }


    //  Add customer to dst trainer
    dstTrainer_p->addCustomer(customer_p);
    //  Add customer orders to dst trainer
    dstTrainer_p->order(this->id, customer_p->order(studio.getWorkoutOptions()), studio.getWorkoutOptions());

    //  Remove customer and customers orders from src trainer.
    srcTrainer_p->removeCustomer(this->id);

    //  Close trainer if her has no customers left.
    if(srcTrainer_p->getCustomers().empty())
        srcTrainer_p->closeTrainer();

    this->complete();
}
std::string MoveCustomer::toString() const{
    string result = "";
    result += "move " + to_string(this->srcTrainer) + " " + to_string(this->dstTrainer) + " " + to_string(this->id) + " ";
    if(this->getStatus() == COMPLETED){
        result += "Completed";
    } else {
        result += this->getErrorMsg();
    }
    return result;
}

//  Close trainer
Close::Close(int id): trainerId(id){}
void Close::act(Studio &studio){
    Trainer* trainer_p = studio.getTrainer(this->trainerId);

    if(trainer_p == nullptr){
        this->error("Trainer does not exist or is not open.");
        return;
    }

    if(!trainer_p->isOpen()){
        this->error("Trainer does not exist or is not open.");
        return;
    }

    trainer_p->closeTrainer();
    this->complete();
}
std::string Close::toString() const{
    string result = "";
    result += "close " + to_string(this->trainerId) + " ";
    if(this->getStatus() == COMPLETED){
        result += "Completed";
    } else {
        result += this->getErrorMsg();
    }
    return result;
}

//  Close all trainer
CloseAll::CloseAll(){}
void CloseAll::act(Studio &studio){
    std::vector<Trainer*> trainers_list = studio.getTrainers();
    //  We need to close the trainers in sequence from lowest id to highest id.
    std::sort(trainers_list.begin(), trainers_list.end());
    for(size_t i = 0; i < trainers_list.size(); i++){
        if(trainers_list[i]->isOpen())
            trainers_list[i]->closeTrainer();
    }
    this->complete();
}
std::string CloseAll::toString() const {
    return "closeall Completed";
}


//  Print workout options
PrintWorkoutOptions::PrintWorkoutOptions(){}
void PrintWorkoutOptions::act(Studio &studio){
    std::vector<Workout> workout_opts = studio.getWorkoutOptions();
    for(size_t i = 0; i < workout_opts.size(); i++){
        cout << workout_opts[i].toString() << endl;
    }
}
std::string PrintWorkoutOptions::toString() const{
    return "workout_options Completed";
};


//  Print trainer status
PrintTrainerStatus::PrintTrainerStatus(int id): trainerId(id){}
void PrintTrainerStatus::act(Studio &studio){
    Trainer* trainer_p = studio.getTrainer(this->trainerId);    

    if(trainer_p == nullptr){
        this->error("Trainer does not exist");
        return;
    }

    cout << "Trainer " + std::to_string(trainer_p->getId()) + " status: " + (trainer_p->isOpen()?"Open":"Closed") << endl;
    cout << "Customers:" << endl;

    std::vector<Customer*> customerList = trainer_p->getCustomers();
    std::vector<OrderPair>& orderList = trainer_p->getOrders();
    for(size_t i = 0; i < customerList.size(); i++){
        cout << customerList[i]->toString() << endl;
    }    
    for(size_t i = 0; i < orderList.size(); i++){
        cout << orderList[i].second.getName() + " " + std::to_string(orderList[i].second.getPrice()) + " " + std::to_string(orderList[i].first) << endl;
    }

}
std::string PrintTrainerStatus::toString() const{
    string result = "";
    result += "status " + to_string(this->trainerId);
    if(this->getStatus() == COMPLETED){
        result += "Completed";
    } else {
        result += this->getErrorMsg();
    }
    return result;
}


//  Print action log
PrintActionsLog::PrintActionsLog(){}
void PrintActionsLog::act(Studio &studio){
    std::vector<BaseAction*> actionLog = studio.getActionsLog();
    for(size_t i = 0; i < actionLog.size(); i++){
        cout << actionLog[i]->toString() << endl;
    }
    this->complete();
}
std::string PrintActionsLog::toString() const{
    return "log Completed";
}

//  Backup studio
BackupStudio::BackupStudio(){}
void BackupStudio::act(Studio &studio){
    studio_backup = Studio(studio);
    this->complete();
}
std::string BackupStudio::toString() const{
    return "backup Completed";
}



