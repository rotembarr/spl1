#include "Studio.h"


Studio::Studio(): 	
	open(false) {
}

Studio::Studio(const std::string &configFilePath) {
	std::ifstream confFile(configFilePath.c_str(), std::ifstream::in);
	std::string line;
	int nOfTrainer;

	if (!confFile.is_open()) {
		std::cout << "Error: Couldn't open config file" << std::endl;
		return;
	}

	// TODO
	std::cout << "file has opened" << std::endl;

	// Num of Trainer
	while (std::getline(confFile, line) && (line == "" || line[0] == '#')) {	
	} 

	std::cout << line << std::endl;
	nOfTrainer = std::stoi(line);

	// Trainers Capacity parsing - create trainers.
	while (std::getline(confFile, line) && (line == "" || line[0] == '#')) {		
	}
	for (int i = 0; i < nOfTrainer; ++i) {
		std::string sCap;
		std::istringstream stream(line);
		std::getline(stream, sCap, ',');
		trainers.push_back(new Trainer(std::stoi(sCap), i));
	}

	// Workouts.
	
	while (std::getline(confFile, line) && line != "" && line[0] != '#') {
	}
	int id = 0;
	while (std::getline(confFile, line)) {
		std::string name, type, price;
		std::istringstream stream(line);
		
		std::getline(stream, name, ',');
		std::getline(stream, type, ',');
		std::getline(stream, price, '\n');

		Workout wo(id, name, std::stoi(price), Workout::strToType(type));
		workout_options.push_back(std::move(wo));
		id++;
	}

	std::cout << "Studio is now open" << std::endl;
}

void Studio::start(){} // TODO

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


