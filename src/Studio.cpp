#include "Studio.h"

Studio::Studio(): 	
	open(true),
	customersCounter(0) {
}

void Studio::clear() {
	while (this->trainers.size() != 0) {
		Trainer *trainer = this->trainers.back();
		delete trainer;
		this->trainers.pop_back();
	}

	while (this->actionsLog.size() != 0) {
		BaseAction *action = this->actionsLog.back();
		delete action;
		this->actionsLog.pop_back();
	}	
}

Studio::~Studio() {
	this->clear();
}

Studio::Studio(const Studio &other): 
	open(other.open),
	customersCounter(0),
	workout_options(other.workout_options) {

	for (size_t i = 0; i < other.actionsLog.size(); i++) {
		this->actionsLog.push_back(actionsLog[i]->clone());
	}


}

// Studio(Studio &&other):
// 	open(other.open),
// 	customersCounter(other.customersCounter),
// 	trainers(other.trainers),
// 	workout_options(other.workout_options),
// 	actionsLog(other.actionsLog) {

// 	other.trainers.clear();
// 	other.workout_options.clear();
// 	other.actionsLog.clear();
// }

// Studio& Studio::operator=(Studio &&other) {
// 	if (this != &other) {
// 		this->clear();
// 		this->open = other.open;
// 		this->customersCounter = other.customersCounter;
// 		this->trainers = other.trainers;
// 		this->workout_options = other.workout_options;
// 		this->actionsLog = other.actionsLog;

// 		other.trainers.clear();
// 		other.workout_options.clear();
// 		other.actionsLog.clear();
// 	}

// 	return (*this);
// }

Studio::Studio(const std::string &configFilePath) : Studio() {
	std::ifstream confFile(configFilePath.c_str(), std::ifstream::in);
	std::string line;
	int nOfTrainer = 0;

	if (!confFile.is_open()) {
		std::cout << "Error: Couldn't open config file" << std::endl;
		return;
	}

	// Num of Trainer
	while (std::getline(confFile, line) && (line == "" || line[0] == '#')) {	
	} 

	// Trainers Capacity parsing - create trainers.
	while (std::getline(confFile, line) && (line == "" || line[0] == '#')) {		
	}

	std::string sCap;
	std::istringstream stream(line);
	for (int i = 0; i < nOfTrainer; ++i) {
		std::getline(stream, sCap, ',');
		trainers.push_back(new Trainer(std::stoi(sCap), i));
	}

	// Workouts.
	while (std::getline(confFile, line) && (line == "" || line[0] == '#')) {
	}

	int id = 0;
	while (std::getline(confFile, line) && (line == "" || line[0] == '#')) {
		std::string name, type, price;
		std::istringstream stream(line);
		
		std::getline(stream, name, ',');
		std::getline(stream, type, ',');
		std::getline(stream, price, ',');
		Workout wo(id, name, std::stoi(price), Workout::strToType(type));
		workout_options.push_back(wo); // TODO
		id++;
	}

	std::cout << "Studio is now open" << std::endl;
}

bool Studio::isOpen () {
	return this->open;
}

void Studio::start() {
	std::string command;

	// Run until close is being performed.
	while (this->isOpen()) {
		
		// Get the user command.
		std::cin >> command;
		std::istringstream stream(command);
		std::getline(stream, command, ' ');

		std::cout << command << std::endl;
		return;

		if (command == "open") {
			std::vector<Customer*> newCustomers;
			std::string sTrainerId;
			std::string sCustomerName;
			std::string sCustomerStrategy;

			// Get trainer id.
			std::getline(stream, sTrainerId, ' ');

			// Get Customers.
			while (std::getline(stream, sCustomerName, ',')) {
				std::getline(stream, sCustomerStrategy, ' ');

				newCustomers.push_back(this->createCustomer(sCustomerStrategy, sCustomerName, customersCounter++));
				// TODO - delete them
				// add the to the main vector
				// 
			}

			// Create action and do it!!
			this->executeAction(new OpenTrainer(std::stoi(sTrainerId), newCustomers));

		// // Order.
		// } else if (command.rfind("order"), 0) {
		// 	std::string sTrainerId;

		// 	// Get trainer id.
		// 	std::getline(stream, sTrainerId, ' ');

		// 	// Create action and do it!!
		// 	this->executeAction(new Order(std::stoi(sTrainerId)));

		// // MoveCustomer.
		// } else if (command.rfind("move"), 0) {
		// 	std::string sSourceTrainerId;
		// 	std::string sDestTrainerId;
		// 	std::string sCustomerId;

		// 	// Get IDs.
		// 	std::getline(stream, sSourceTrainerId, ' ');
		// 	std::getline(stream, sDestTrainerId, ' ');
		// 	std::getline(stream, sCustomerId, ' ');
			
		// 	// Create action and do it!!
		// 	this->executeAction(new MoveCustomer(std::stoi(sSourceTrainerId), std::stoi(sDestTrainerId), std::stoi(sCustomerId)));

		// // Close.
		// } else if (command.rfind("close"), 0) {
		// 	std::string sTrainerId;

		// 	// Get trainer id.
		// 	std::getline(stream, sTrainerId, ' ');

		// 	// Create action and do it!!
		// 	this->executeAction(new Close(std::stoi(sTrainerId)));

		// // CloaseAll.
		// } else if (command.rfind("closeall"), 0) {

		// 	// Create action and do it!!
		// 	this->executeAction(new CloseAll());

		// // PrintWorkoutOptions.
		// } else if (command.rfind("workout_options"), 0) {

		// 	// Create action and do it!!
		// 	this->executeAction(new PrintWorkoutOptions());

		// // PrintTrainerStatus.
		// } else if (command.rfind("status"), 0) {
		// 	std::string sTrainerId;

		// 	// Get trainer id.
		// 	std::getline(stream, sTrainerId, ' ');

		// 	// Create action and do it!!
		// 	this->executeAction(new PrintTrainerStatus(std::stoi(sTrainerId)));

		// // PrintActionsLog.
		// } else if (command.rfind("log"), 0) {

		// 	// Create action and do it!!
		// 	this->executeAction(new PrintActionsLog());
		
		// // BackupStudio.
		// } else if (command.rfind("backup"), 0) {

		// 	// Create action and do it!!
		// 	this->executeAction(new BackupStudio());
		
		// // RestoreStudio.
		// } else if (command.rfind("restore"), 0) {

		// 	// Create action and do it!!
		// 	this->executeAction(new RestoreStudio());

		} else {
			std::cout << "No such command -" + command << std::endl;
			continue;
		}

	}
} 

int Studio::getNumOfTrainers() const {
	return this->trainers.size();
}

Trainer* Studio::getTrainer(int tid) {
	for (Trainer* trainer : trainers) {
		if (trainer->getId() == tid) {
			return trainer;
		}
	}

	return nullptr;
}

const std::vector<BaseAction*>& Studio::getActionsLog() const {
	return this->actionsLog;
}

std::vector<Workout>& Studio::getWorkoutOptions() {
	return this->workout_options;
}

std::vector<Trainer*> Studio::getTrainers() const {
	return this->trainers;
}

Customer* Studio::createCustomer(std::string type, std::string name, int id) const {
	if (type == "swt") {
		return new SweatyCustomer(name, id);
	} else if (type == "chp") {
		return new CheapCustomer(name, id);
	} else if (type == "mcl") {
		return new HeavyMuscleCustomer(name, id);
	} else if (type == "fbd") {
		return new FullBodyCustomer(name, id);
	} else {
		std::cout << "Error: Bad type of Customer" << std::endl;
		return nullptr;
	}
}

void Studio::executeAction(BaseAction* action) {
	
	action->act(*this);
	std::cout << action->toString() << std::endl;

	// End of action.
	this->actionsLog.push_back(action);
}