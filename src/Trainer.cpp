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

Trainer::Trainer(const Trainer& other): 
	capacity(other.capacity),
	id(other.id),
	open(other.open), 
	orderList(other.orderList) {

	for (std::size_t i = 0; i < other.customersList.size(); i++) {
		this->customersList.push_back(other.customersList[i]->clone()); // new
	}

}


Trainer::Trainer(Trainer&& other):
	capacity(other.capacity),
	id(other.id),
	open(other.open),
	customersList(other.customersList),
	orderList(other.orderList) {

	other.customersList.clear();
	other.orderList.clear();

}

// Copy assignment.
Trainer& Trainer::operator=(const Trainer& other) {

	if (this != &other) {
		this->clear();
		this->capacity 	= other.capacity;
		this->salary 	= other.salary;
		this->id 		= other.id;
		this->open 		= other.open;

		for (std::size_t i = 0; i < other.customersList.size(); i++) {
			this->customersList.push_back(other.customersList[i]->clone()); // new
		}

		this->orderList = std::vector<OrderPair>(other.orderList);
	}

	return *this;
}

Trainer& Trainer::operator=(Trainer&& other) {

	if (this != &other) {
		this->clear();
		this->capacity 		= other.capacity;
		this->id 			= other.id;
		this->open 			= other.open;
		this->customersList = other.customersList;
		this->orderList 	= std::vector<OrderPair>(other.orderList);

		other.customersList.clear();
		other.orderList.clear();
	}

	return *this;
}

// Delete all customers.
void Trainer::delAllCustomers() {
	while (this->customersList.size() != 0) {
		Customer* temp = this->customersList.back();
		this->customersList.pop_back();
		delete temp;
	}
}

void Trainer::clear() {
	this->capacity 	= 0;
	this->salary 	= 0;
	this->id 		= 0;
	this->open 		= 0;
	this->delAllCustomers();
	this->orderList.clear();
}

// Destructor.
Trainer::~Trainer() {
	this->clear();
}

int Trainer::getCapacity() const {
	return this->capacity;
}

int Trainer::getId() const {
	return this->id;
}

void Trainer::addCustomer(Customer* customer) {
	if (!this->isOpen()) {
		std::cout << "Int-Error: Add Customer to a close Trainer number " + std::to_string(this->getId()) << std::endl;
	}

	if (customer == nullptr) {
		std::cout << "Int-Error: null ptr argument" << std::endl;
	}

    if(this->customersList.size() < (size_t)this->getCapacity()) {
        this->customersList.push_back(customer);
    } else {
		std::cout << "Int-Error: too many customers added to Trainer" + std::to_string(this->getId()) << std::endl;
    }
}

void Trainer::delCustomerOrder(int id) {
	std::vector<OrderPair> newOrderList;

	for (std::size_t i = 0; i < this->orderList.size(); i++) {
		if (this->orderList[i].first == id) {
			this->salary -= this->orderList[i].second.getPrice();
		} else {
			newOrderList.push_back(this->orderList[i]);
		}
	} 

	this->orderList = std::vector<OrderPair>(newOrderList);
}

// Remove costumer because moving it to another trainer.
// ! Dangare: This function doesnt free customer memory
void Trainer::removeCustomer(int id) { 

	if (!this->isOpen()) {
		std::cout << "Int-Error: Remove Customer from a close Trainer number " + std::to_string(this->getId()) << std::endl;
	}

	// Erase all customer's order from oder list.
	this->delCustomerOrder(id);

	// Delete customer.
    for(size_t i = 0; i < this->customersList.size(); i++) {
        if(this->customersList[i]->getId() == id) {
            this->customersList.erase(this->customersList.begin() + i);
			return;
		}
    }
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
		// Customers go home - delete them but keep their workouts.
		this->delAllCustomers();

		// Close terminal.
		this->open = false;
		// TODO std::cout << "Trainer " + std::to_string(this->id) + " closed. Salary " + std::to_string(this->getSalary()) + "NIS" << std::endl;
	}

	
}

int Trainer::getSalary() {
    return this->salary;
}

bool Trainer::isOpen() { 
	return this->open; 
}


std::string Trainer::toString() const {
	std::string out;

	out = "Trainer " + std::to_string(this->id) + " status: " + (this->open ? "open" : "closed") + "\n";
	
	if (this->isOpen) {
		out += "Customers:\n";
		for (std::size_t i = 0; i < this->customersList.size(); i++) {
			out += this->customersList[i]->toString() + "\n";
		}

		out += "Orders:\n";
		for (std::size_t i = 0; i < this->orderList.size(); i++) {
			out += this->orderList[i].second.getName() + " " + std::to_string(this->orderList[i].second.getPrice()) + "NIS " + std::to_string(this->orderList[i].first) + "\n";
		}

		out += this->getSalary();
	}
	
	return out;
}