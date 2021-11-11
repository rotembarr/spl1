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

void Trainer::addCustomer(Customer* customer) {
	if (customer == null) {
		throw "null ptr argument";
	}

	this->customerList.push_back(customer);
}

void Trainer::removeCustomer(int id) {
	int cIndex = -1;
	int cId = -1;

	// Find customer index
	for (std::vector<Customer*>::size_type i = 0; i < this->customerList.size(); i++) {
		if (this->customerList[i]->getId() == id) {
			cIndex = i;
			id = this->customerList[i]->getId();
		}
	}

	if (cIndex == -1) {
		return; // TODO
	}

	// Remove customer orders.
	int i = 0;
	for (OrderPair p : orderList) {
		if (std::get<0>(p) == cId) {
			orderList.erase(i);
		}
		i++;
	}

	// Remove customer object.
	this->customerList.erase(cIndex);

}

Customer* Trainer::getCustomer(int id) {
	for (std::vector<Customer*>::size_type i = 0; i < this->customerList.size(); i++) {
		if (this->customerList[i]->getId() == id) {
			return this->customerList[i];
		}
	}
}

std::vector<Customer*>& Trainer::getCustomers() {
	return this.customerList;
}
std::vector<OrderPair>& Trainer::getOrders() {
	return this->orderList;
}

void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options);

void Trainer::openTrainer();

void Trainer::closeTrainer() {
	std::string s = "Trainer " + std::to_string(this->id) + " closed. Salary " + + "NIS";
	std::cout << 
}

int Trainer::getSalary() {
	int salary = 0;

	for (OrderPair p : orderList) {
		salary += std::get<1>(p).getPrice();
	}

	return salary;
}

bool Trainer::isOpen() {
	return this->open;
}

std::string Trainer::toString() const {
	std::string s = "Trainer " + std::to_string(this->id) + " status: " + (this.open ? "open" : " close") + "\n";

	if (!this->isOpen())
		return s;

	// Print Costumers.
	s += "Customers\n"
	for (Customer* c : this->customerList) {
		s += std::to_string(c->getId()) + " " + c->getName() + "\n"; 
	}

	// Print Orders.
	s += "Orders\n"
	for (OrderPair op : this->orderList) {
		s += std::get<1>(op).getName() + " " + std::to_string(std::get<1>(op).getPrice()) + "NIS " + std::to_string(std::get<1>(op)) + "\n"; 
	}

	// Print salary.
	s += "Current Trainer's Salary:" + std::to_string(this->getSalary()) + "NIS\n";

	return s;
}
