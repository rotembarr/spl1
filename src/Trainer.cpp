#include "Trainer.h"

Trainer::Trainer(int t_capacity): 
	capacity(t_capacity),
	salary(0),
	id(0),
	open(false) {
}

Trainer::Trainer(int t_capacity, int t_id): 
	capacity(t_capacity),
	salary(0),
	id(t_id),
	open(false) {
}

// Delete all customers.
void Trainer::delAllCustomers() {
	while (this->customersList.size() != 0) {
		Customer* temp = this->customersList.back();
		this->customersList.pop_back();
		delete temp;
	}
}

// Destructor.
Trainer::~Trainer() {
	this->delAllCustomers();
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

// Remove costumer because moving to other trainer.
void Trainer::removeCustomer(int id) { // This function doesnt free customer
	//	Remove customer from customerList
    for(size_t i = this->customersList.size() - 1; i >= 0 ; i--){
        if(this->customersList[i]->getId() == this->id) {
            this->customersList[i] = nullptr;
		}
    }

	//	Remove customer order from orderList
	std::vector<OrderPair> orderListFiltered = std::vector<OrderPair>();
	for(size_t i = this->orderList.size() - 1; i >= 0; i--){
		if(this->orderList[i].first != this->id){
			orderListFiltered.push_back(this->orderList[i]);
		}
	}
	this->orderList = std::vector<OrderPair>(orderListFiltered);
}

Customer* Trainer::getCustomer(int id) {
    for (std::vector<Customer*>::size_type i = 0; i < this->customersList.size(); i++) {
		if (this->customersList[i]->getId() == id) {
			return this->customersList[i];
		}
	}

    return nullptr;
}

std::vector<Customer*>& Trainer::getCustomers() { 
	return this->customersList; 
}

std::vector<OrderPair>& Trainer::getOrders() { 
	return this->orderList; 
}

void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options){
    for(int workout_id : workout_ids){
        for(Workout wo_option : workout_options){
            if(wo_option.getId() == workout_id) {
                this->orderList.push_back(OrderPair(customer_id, wo_option));
                this->salary += wo_option.getPrice();
            }
        }
    }

    // TODO - print
}

void Trainer::openTrainer() {

	if (this->isOpen()) {
		std::cout << "Workout session does not exist or is already open" << std::endl;
	}

	this->open = true;
} 

void Trainer::closeTrainer() {

	if (!this->isOpen()) {
		std::cout << "Trainer does not exist or is not open" << std::endl;
	} else {
		//	Accumulate paycheck
		this->salary += this->calcSalary();

		// Customers go home - they will be delete in the studio.
		this->customersList.clear();
		this->orderList.clear();

		// Close terminal.
		this->open = false;
		std::cout << "Trainer " + std::to_string(this->id) + " closed. Salary " + std::to_string(this->getSalary()) + "NIS" << std::endl;
	}

	
}

int Trainer::calcSalary() const {
	int paycheck = 0;

    for(size_t i = 0; i < this->orderList.size(); i++) {
        paycheck += this->orderList[i].second.getPrice();
    }

    return paycheck;
}

int Trainer::getSalary() {
    return this->salary;
}

bool Trainer::isOpen() { 
	return this->open; 
}

bool Trainer::operator<(const Trainer &b) const{
	if(this->getId() < b.getId())
		return true;
	return false;
}
bool Trainer::operator>(const Trainer &b) const{
	if(this->getId() > b.getId())
		return true;
	return false;
}
