#include "Action.h"
#include "Studio.h"

//  Base Action

BaseAction::BaseAction(){
    this->errorMsg = "";
    this->status = RUNNING;
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
    for(int i = 0; i < this->customers.size(); i++){
        trainer->addCustomer(this->customers[i]);
    }
}
std::string OpenTrainer::toString() const{
    return "open " + std::to_string(this->trainerId);
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
    for(int i = 0; i < customer_list.size(); i++){
        trainer->order(customer_list[i]->getId(), customer_list[i]->order(studio.getWorkoutOptions()), studio.getWorkoutOptions());
    }
    this->complete();
}
std::string Order::toString() const{
    return "order " + this->trainerId;
}

//  Move customer
MoveCustomer::MoveCustomer(int src, int dst, int customerId): srcTrainer(src), dstTrainer(dst), id(customerId) {}
void MoveCustomer::act(Studio &studio){

    //  Get trainers and customer.
    Trainer* srcTrainer_p = studio.getTrainer(this->srcTrainer);
    Trainer* dstTrainer_p = studio.getTrainer(this->dstTrainer);
    Customer* customer_p = srcTrainer_p->getCustomer(this->id);


    //  No trainer / customer exists
    if(srcTrainer_p == nullptr | dstTrainer_p == nullptr | customer_p == nullptr){
        this->error("Cannot move costumer");
        return;
    }

    //  Either trainer is closed
    if(!srcTrainer_p->isOpen() | !dstTrainer_p->isOpen()){
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

}

//  Close trainer
Close::Close(int id): trainerId(id){}
void Close::act(Studio &studio){
    Trainer* trainer_p = studio.getTrainer(this->trainerId);

    trainer_p->closeTrainer();



}
std::string Close::toString() const{

}



