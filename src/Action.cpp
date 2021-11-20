#include "Action.h"
#include "Studio.h"

extern Studio* backup;


//  Base Action
BaseAction::BaseAction():
    status() {
}

BaseAction::~BaseAction(){} // For warnings

BaseAction::BaseAction(const BaseAction &other):
    errorMsg(other.errorMsg),
    status(other.status) {
}

ActionStatus BaseAction::getStatus() const {
    return this->status;
}

void BaseAction::complete() {
    this->status = COMPLETED;
}

void BaseAction::error(std::string errorMsg) {
    this->errorMsg = errorMsg;
    this->status = ERROR;
}

std::string BaseAction::getErrorMsg() const{
    return this->errorMsg;
}


//  Open Trainer
OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList): 
    trainerId(id), 
    customers(customersList) { 
}

OpenTrainer::OpenTrainer(const OpenTrainer &other):
    BaseAction(other),
    trainerId(other.trainerId) {
    // customers(other.customers) { // TODO
} // TODO

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

    trainer->openTrainer();
    for(size_t i = 0; i < this->customers.size(); i++){
        trainer->addCustomer(this->customers[i]);
    }
}

std::string OpenTrainer::toString() const{
    std::string result = "";

    result += "open " + std::to_string(this->trainerId) + " ";
    for(size_t i = 0; i < this->customers.size(); i++){
        result += this->customers[i]->getName() + "," + this->customers[i]->customer_type() + " ";
    }

    if(this->getStatus() == COMPLETED){
        result += "Completed";
    } else {
        result += "Error: " + this->getErrorMsg();
    }
    return result;
}

BaseAction* OpenTrainer::clone() const {
    return new OpenTrainer(*this); 
}

//  Order
Order::Order(int id): trainerId(id) {}

Order::Order(const Order &other): 
    BaseAction(other),  
    trainerId(other.trainerId) {
}


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
    std::string result = "";
    result += "order " + std::to_string(this->trainerId) + " ";
    if(this->getStatus() == COMPLETED){
        result += "Completed";
    } else {
        result += "Error: " + this->getErrorMsg();
    }
    return result;
}

BaseAction* Order::clone() const {
    return new Order(*this); 
}


//  Move customer
MoveCustomer::MoveCustomer(int src, int dst, int customerId): 
    srcTrainer(src), 
    dstTrainer(dst), 
    id(customerId) {        
}


MoveCustomer::MoveCustomer(const MoveCustomer &other): 
    BaseAction(other),  
    srcTrainer(other.srcTrainer),
    dstTrainer(other.dstTrainer),
    id(other.id) {
}


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
    std::string result = "";
    result += "move " + std::to_string(this->srcTrainer) + " " + std::to_string(this->dstTrainer) + " " + std::to_string(this->id) + " ";
    if(this->getStatus() == COMPLETED){
        result += "Completed";
    } else {
        result += "Error: " + this->getErrorMsg();
    }
    return result;
}

BaseAction* MoveCustomer::clone() const {
    return new MoveCustomer(*this); 
}


//  Close trainer
Close::Close(int id): trainerId(id){}


Close::Close(const Close &other): 
    BaseAction(other),  
    trainerId(other.trainerId) {
}

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
    std::string result = "";

    result += "close " + std::to_string(this->trainerId) + " ";
    if(this->getStatus() == COMPLETED){
        result += " Completed";
    } else {
        result += " Error: " + this->getErrorMsg();
    }
    return result;
}

BaseAction* Close::clone() const {
    return new Close(*this); 
}

//  Close all trainer
CloseAll::CloseAll(){}

CloseAll::CloseAll(const CloseAll &other): 
    BaseAction(other) {
}

void CloseAll::act(Studio &studio){

    //  We need to close the trainers in sequence from lowest id to highest id.
    int nOfTrainer = studio.getNumOfTrainers();
    for (int i = 0; i < nOfTrainer; i++) {
        Trainer* trainer = studio.getTrainer(i);

        if ((trainer != nullptr) && (trainer->isOpen())) {
            trainer->closeTrainer();
        }
    }

    this->complete();
}

std::string CloseAll::toString() const {
    return "closeall Completed";
}

BaseAction* CloseAll::clone() const {
    return new CloseAll(*this); 
}


//  Print workout options
PrintWorkoutOptions::PrintWorkoutOptions(){}


PrintWorkoutOptions::PrintWorkoutOptions(const PrintWorkoutOptions &other): 
    BaseAction(other) {
}


void PrintWorkoutOptions::act(Studio &studio){
    std::vector<Workout> workout_opts = studio.getWorkoutOptions();
    for(size_t i = 0; i < workout_opts.size(); i++){
        std::cout << workout_opts[i].toString() << std::endl;
    }
}

std::string PrintWorkoutOptions::toString() const{
    return "workout_options Completed";
};

BaseAction* PrintWorkoutOptions::clone() const {
    return new PrintWorkoutOptions(*this); 
}


//  Print trainer status
PrintTrainerStatus::PrintTrainerStatus(int id): trainerId(id){}

PrintTrainerStatus::PrintTrainerStatus(const PrintTrainerStatus &other): 
    BaseAction(other),
    trainerId(other.trainerId) {
}

void PrintTrainerStatus::act(Studio &studio){
    Trainer* trainer = studio.getTrainer(this->trainerId);    

    if(trainer == nullptr){
        this->error("Trainer does not exist");
        return;
    }

    std::cout << trainer->toString() << std::endl;
}

std::string PrintTrainerStatus::toString() const{
    std::string result = "";

    result += "status " + std::to_string(this->trainerId) + " ";
    if(this->getStatus() == COMPLETED){
        result += "Completed";
    } else {
        result += "Error: " + this->getErrorMsg();
    }
    return result;
}

BaseAction* PrintTrainerStatus::clone() const {
    return new PrintTrainerStatus(*this); 
}


//  Print action log
PrintActionsLog::PrintActionsLog(){}

PrintActionsLog::PrintActionsLog(const PrintActionsLog &other): 
    BaseAction(other) {
}

void PrintActionsLog::act(Studio &studio){
    std::vector<BaseAction*> actionLog = studio.getActionsLog();
    for(size_t i = 0; i < actionLog.size(); i++){
        std::cout << actionLog[i]->toString() << std::endl;
    }
    this->complete();
}
std::string PrintActionsLog::toString() const{
    return "log Completed";
}

BaseAction* PrintActionsLog::clone() const {
    return new PrintActionsLog(*this); 
}

//  Backup studio
BackupStudio::BackupStudio(){}

BackupStudio::BackupStudio(const BackupStudio &other): 
    BaseAction(other) {
}

void BackupStudio::act(Studio &studio){
    backup = new Studio(studio);
    this->complete();
}

std::string BackupStudio::toString() const{
    return "backup Completed";
}

BaseAction* BackupStudio::clone() const {
    return new BackupStudio(*this); 
}

// Restore studio.
RestoreStudio::RestoreStudio() {}

RestoreStudio::RestoreStudio(const RestoreStudio &other): 
    BaseAction(other) {
}


void RestoreStudio::act(Studio &studio) {
    studio = *backup;
}

std::string RestoreStudio::toString() const {
    return "restore Completed";
}

BaseAction* RestoreStudio::clone() const {
    return new RestoreStudio(*this); 
}