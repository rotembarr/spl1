#include "../include/Trainer.h"

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

	this->customersList.push_back(customer);
}

void Trainer::removeCustomer(int id) {
	int cIndex = -1;

	// Find customer index
	for (std::vector<Customer*>::size_type i = 0; i < this->customersList.size(); i++) {
		if (this->customersList[i]->getId() == id) {
			cIndex = i;
		}
	}

	if (cIndex == -1) {
		return; // TODO
	}

	// Remove customer object. TODO
	this->customersList.erase(this->customersList.begin() + cIndex);

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

void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options) {} //TODO

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
	return this->calcSalary();
}

bool Trainer::isOpen() {
	return this->open;
}

std::string Trainer::toString() const {
	std::string s = ("Trainer " + std::to_string(this->id) + " status: " + (this->open ? "open" : " close") + "\n");

	if (!this->open)
		return s;

	// Print Costumers.
	s += "Customers\n";
	for (Customer* c : this->customersList) {
		s += std::to_string(c->getId()) + " " + c->getName() + "\n"; 
	}

	// Print Orders.
	s += "Orders\n";
	for (OrderPair op : this->orderList) {
		s += std::get<1>(op).getName() + " " + std::to_string(std::get<1>(op).getPrice()) + "NIS " + std::to_string(std::get<0>(op)) + "\n"; 
	}

	// Print salary.
	s += "Current Trainer's Salary:" + std::to_string(this->calcSalary()) + "NIS\n";

	return s;
}

int Trainer::calcSalary() const {
	int salary = 0;

	for (OrderPair p : orderList) {
		salary += std::get<1>(p).getPrice();
	}

	return salary;
}