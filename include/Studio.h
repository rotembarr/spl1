#ifndef STUDIO_H_
#define STUDIO_H_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Workout.h"
#include "Trainer.h"
#include "Action.h"


class Studio{		
public:
    // Rule of 5.
	Studio();
    Studio(const std::string &configFilePath);
    virtual ~Studio();
    Studio(const Studio &other);
    // Studio(Studio &&other);
    Studio& operator=(Studio &&other);

    // Functianality.
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();
    bool isOpen();
protected:
    Customer* createCustomer(std::string type, std::string name, int id) const;
    void executeAction(BaseAction* action);
    void clear();
private:
    bool open;
    int customersCounter;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
};

#endif