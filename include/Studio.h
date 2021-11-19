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
	Studio();
    Studio(const std::string &configFilePath);

    // Rule of 5.
    Studio(const Studio &other);
    Studio(Studio &&other);
    Studio& operator=(const Studio &other);
    Studio& operator=(Studio &&other);
    virtual ~Studio();

    // Functianality.
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();
    std::vector<Trainer*> getTrainers() const;
    bool isOpen();
protected:
    Customer* createCustomer(std::string type, std::string name, int id);
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
