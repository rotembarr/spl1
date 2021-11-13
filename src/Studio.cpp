Studio();
Studio(const std::string &configFilePath);
void start();
int getNumOfTrainers() const;
Trainer* getTrainer(int tid);
const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
std::vector<Workout>& getWorkoutOptions();


