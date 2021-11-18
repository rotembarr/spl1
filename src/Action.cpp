#include "Action.h"
#include "Studio.h"

BaseAction::BaseAction():
    status(IN_PROGRESS) {

}

BaseAction::BaseAction(const BaseAction &other): 
    errorMsg(other.errorMsg),
    status(other.status) {     
}

BaseAction::~BaseAction() {

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

std::string BaseAction::getErrorMsg() const {
    return this->errorMsg;
}


/////////////////////////// Open Trainer //////////////////////////
OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList):
    trainerId(id),
    customers(customersList) {

}

OpenTrainer::OpenTrainer(const OpenTrainer &other): 
    BaseAction(other),
    trainerId(other.trainerId),
    customers(other.customers) {

}

void OpenTrainer::act(Studio& studio) {
    
    Trainer* trainer = studio.getTrainer(this->trainerId);

    trainer->openTrainer();
    for (std::size_t j = 0; j < this->customers.size(); j++) {
        trainer->addCustomer(this->customers[j]);
    }

}

std::string OpenTrainer::toString() const {
    return "OpenTrainer";
}

BaseAction* OpenTrainer::clone() const {
    BaseAction* a = new OpenTrainer((*this));
    return (a);
}