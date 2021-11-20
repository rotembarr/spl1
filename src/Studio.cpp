#include "Studio.h"

extern Studio* backup;

Studio::Studio(): 	
	open(true),
	customersCounter(0) {
}

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
	nOfTrainer = std::stoi(line);

	// Trainers Capacity parsing - create trainers.
	while (std::getline(confFile, line) && (line == "" || line[0] == '#')) {		
	}

	std::string sCapacity;
	std::istringstream stream(line);
	for (int i = 0; i < nOfTrainer; ++i) {
		std::getline(stream, sCapacity, ',');
		this->trainers.push_back(new Trainer(std::stoi(sCapacity), i));
	}

	// Workouts.	
	while (std::getline(confFile, line) && (line == "" || line[0] == '#')) {
	}


	int id = 0;
	while ((line != "" && line[0] != '#')) {
		std::string name, type, price, space;
		std::istringstream stream(line);
		
		std::getline(stream, name, ',');
		std::getline(stream, space, ' ');
		std::getline(stream, type, ',');
		std::getline(stream, space, ' ');
		std::getline(stream, price, ',');

		workout_options.push_back(Workout(id, name, std::stoi(price), Workout::strToType(type))); 
		id++;

		std::getline(confFile, line);
	}

	std::cout << "Studio is now open" << std::endl;
}

Studio::Studio(const Studio &other): 
	open(other.open),
	customersCounter(0),
	workout_options(other.workout_options) {

	// Copy trainers.
	for (std::size_t i = 0; i < other.trainers.size(); i++) {
		this->trainers.push_back(new Trainer(*other.trainers[i])); // new
	}

	// Copy action log.
	for (size_t i = 0; i < other.actionsLog.size(); i++) {
		this->actionsLog.push_back(actionsLog[i]);
	}
}

Studio::Studio(Studio &&other):
	open(other.open),
	customersCounter(other.customersCounter),
	trainers(other.trainers),
	workout_options(other.workout_options),
	actionsLog(other.actionsLog) {

	other.trainers.clear();
	other.workout_options.clear();
	other.actionsLog.clear();
}

Studio& Studio::operator=(const Studio &other) {

	if (this != &other) {
		this->clear();
		this->open 				= other.open;
		this->customersCounter	= other.customersCounter;
		this->workout_options 	= std::vector<Workout>(other.workout_options);

		// Copy trainers.
		for (std::size_t i = 0; i < other.trainers.size(); i++) {
			this->trainers.push_back(new Trainer(*other.trainers[i])); // new
		}

		// Copy action log (deep copy is actually happend).
		for (size_t i = 0; i < other.actionsLog.size(); i++) {
			this->actionsLog.push_back(actionsLog[i]);
		}
	}

	return *this;

}


Studio& Studio::operator=(Studio &&other) {
	if (this != &other) {
		this->clear();
		this->open 				= other.open;
		this->customersCounter	= other.customersCounter;
		this->trainers 			= other.trainers;
		this->workout_options 	= std::vector<Workout>(other.workout_options);
		this->actionsLog 		= other.actionsLog;

		other.trainers.clear();
		other.workout_options.clear();
		other.actionsLog.clear();
	}

	return (*this);
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

bool Studio::isOpen () {
	return this->open;
}

void Studio::start() {

	// Run until close is being performed.
	while (this->isOpen()) {
		std::vector<std::string> command;
		
		// Get the user command.
		std::string line;
	    std::getline(std::cin, line);
		std::istringstream stream(line);

		// Parse command
		std::string word;
		while (stream >> word) {
			command.push_back(word);
		}

		if (command[0].compare("open") == 0) {
			std::vector<Customer*> newCustomers;
			std::string sTrainerId = command[1];

			for (std::size_t i = 2; i < command.size(); i++) {
				std::string sCustomerName = command[i].substr(0,command[i].size()-4);
				std::string sCustomerStrategy = command[i].substr(command[i].size()-3,command[i].size()-1);

				newCustomers.push_back(this->createCustomer(sCustomerStrategy, sCustomerName, this->customersCounter++));
			}

			// Create action and do it!!
			this->executeAction(new OpenTrainer(std::stoi(sTrainerId), newCustomers));


		// Order.
		} else if (command[0].compare("order") == 0) {
			std::string sTrainerId = command[1];

			// Create action and do it!!
			this->executeAction(new Order(std::stoi(sTrainerId)));

		// MoveCustomer.
		} else if (command[0].compare("move") == 0) {
			std::string sSourceTrainerId = command[1];
			std::string sDestTrainerId = command[2];
			std::string sCustomerId = command[3];
			
			// Create action and do it!!
			this->executeAction(new MoveCustomer(std::stoi(sSourceTrainerId), std::stoi(sDestTrainerId), std::stoi(sCustomerId)));

		// Close.
		} else if (command[0].compare("close") == 0) {
			std::string sTrainerId = command[1];

			// Create action and do it!!
			this->executeAction(new Close(std::stoi(sTrainerId)));

		// CloaseAll.
		} else if (command[0].compare("closeall") == 0) {

			// Create action and do it!!
			this->executeAction(new CloseAll());

			// close studio
			this->open = false;

		// PrintWorkoutOptions.
		} else if (command[0].compare("workout_options") == 0) {

			// Create action and do it!!
			this->executeAction(new PrintWorkoutOptions());

		// PrintTrainerStatus.
		} else if (command[0].compare("status") == 0) {
			std::string sTrainerId = command[1];

			// Create action and do it!!
			this->executeAction(new PrintTrainerStatus(std::stoi(sTrainerId)));

		// PrintActionsLog.
		} else if (command[0].compare("log") == 0) {

			// Create action and do it!!
			this->executeAction(new PrintActionsLog());
		
		// BackupStudio.
		} else if (command[0].compare("backup") == 0) {

			// Create action and do it!!
			this->executeAction(new BackupStudio());
		
		// RestoreStudio.
		} else if (command[0].compare("restore") == 0) {

			// Create action and do it!!
			this->executeAction(new RestoreStudio());

		} else {
			std::cout << "No such command - " + command[0] << std::endl;
			continue;
		}

	}
} 

int Studio::getNumOfTrainers() const {
	return this->trainers.size();
}

Trainer* Studio::getTrainer(int tid) {

	for (std::size_t i = 0; i < this->trainers.size(); i++) {
		if (this->trainers[i]->getId() == tid) {
			return this->trainers[i];
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

Customer* Studio::createCustomer(std::string type, std::string name, int id) {
	Customer* out = nullptr;
	
	if (type.compare("swt") == 0) {
		out = new SweatyCustomer(name, id);
	} else if (type.compare("chp") == 0) {
		out = new CheapCustomer(name, id);
	} else if (type.compare("mcl") == 0) {
		out = new HeavyMuscleCustomer(name, id);
	} else if (type.compare("fbd") == 0) {
		out = new FullBodyCustomer(name, id);
	} else {
		std::cout << "Error: Bad type of Customer" << std::endl;
	}

	return out;
}

void Studio::executeAction(BaseAction* action) {

	action->act(*this);

	// End of action.
	this->actionsLog.push_back(action);
}