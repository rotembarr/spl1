#include "Trainer.h"

Trainer::Trainer(int t_capacity): capacity(t_capacity) {
    this->open = false;
    this->customersList = std::vector<Customer*>();
    this->orderList = std::vector<OrderPair>();
}
int Trainer::getCapacity() const { return this->capacity; } 
void Trainer::addCustomer(Customer* customer) { 
    if(this->customersList.size() < (size_t)this->capacity)
        this->customersList.push_back(customer);
}
void Trainer::removeCustomer(int id) {
    for(std::vector<Customer*>::iterator it = this->customersList.begin(); it != this->customersList.end(); ++it){
        if((*it)->getId() == id)
            this->customersList.erase(it);
    }
}
Customer* Trainer::getCustomer(int id){
    for(Customer* customer : this->customersList){
        if(customer->getId() == id)
            return customer;
    }
    return nullptr;
}
std::vector<Customer*>& Trainer::getCustomers() { return this->customersList; }
std::vector<OrderPair>& Trainer::getOrders() { return this->orderList; }
void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options){
    for(int workout_id : workout_ids){
        for(Workout wo_option : workout_options){
            if(wo_option.getId() == workout_id)
                this->orderList.push_back(OrderPair(customer_id, wo_option));
        }
    }
}
void Trainer::openTrainer() { this->open = true; }
void Trainer::closeTrainer() { this->open = false; }
int Trainer::getSalary() {
    int paycheck = 0;
    for(OrderPair order_pair : this->orderList){
        paycheck += order_pair.second.getPrice();
    }
    return paycheck;
}
bool Trainer::isOpen() { return this->open; }