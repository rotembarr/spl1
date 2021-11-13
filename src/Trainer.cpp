#include "Trainer.h"

Trainer::Trainer(int t_capacity): 
	capacity(t_capacity),
	id(0),
	open(false) {
}

Trainer::Trainer(int t_capacity, int t_id): 
	capacity(t_capacity),
	id(t_id),
	open(false) {
}

int Trainer::getCapacity() const {
	return this->capacity;
}

int Trainer::getId() const {
	return this->id;
}

void Trainer::addCustomer(Customer* customer) {
	if (customer == nullptr) {
		std::cout << "Int-Error: null ptr argument" << std::endl;
	}

    if(this->customersList.size() < (size_t)this->getCapacity())
        this->customersList.push_back(customer);
}

void Trainer::removeCustomer(int id) {
    for(size_t i = 0; i < this->customersList.size(); i++){
        if(this->customersList[i]->getId() == id) {
            this->customersList.erase(this->customersList.begin() + i);
		return;
	}
    }
}

Customer* Trainer::getCustomer(int id){
    for (std::vector<Customer*>::size_type i = 0; i < this->customersList.size(); i++) {
		if (this->customersList[i]->getId() == id) {
			return this->customersList[i];
		}
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
void Trainer::openTrainer() {

	if (this->isOpen()) {
		std::cout << "Workout session does not exist or is already open" << std::endl;
	} 

	this->open = true;
} 

void Trainer::closeTrainer() {
	std::string s;

	if (!this->isOpen()) {
		s = "Trainer does not exist or is not open";
	} else {
		s = "Trainer " + std::to_string(this->id) + " closed. Salary " + std::to_string(this->getSalary()) + "NIS";
	}

	std::cout << s << std::endl;

	this->open = false;
}

int Trainer::getSalary() {
    int paycheck = 0;
    for(size_t i = 0; i < this->orderList.size(); i++) {
        paycheck += this->orderList[i].second.getPrice();
    }

    return paycheck;
}
bool Trainer::isOpen() { return this->open; }
