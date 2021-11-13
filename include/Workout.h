#ifndef WORKOUT_H_
#define WORKOUT_H_

#include <string>

enum WorkoutType{
    ANAEROBIC, MIXED, CARDIO
};

class Workout{
public:
    Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type);     // Constructor
    Workout(const Workout& other);
    int getId() const;
    std::string getName() const;
    int getPrice() const;
    WorkoutType getType() const;
    bool operator<(const Workout &b) const;
    bool operator>(const Workout &b) const;

private:
	const int id;
    const std::string name;
    const int price;
    const WorkoutType type;
};

class Workout_comp_high_to_low {
    public :
        bool operator()(const Workout* a, const Workout* b) const {
            if(a->getPrice() > b->getPrice())
                return true;
            if(b->getPrice() > a->getPrice())
                return false;
            return a->getId() < b->getId();
        }
};

class Workout_comp_low_to_high {
    public: 
        bool operator()(const Workout* a, const Workout* b) const {
            if(a->getPrice() < b->getPrice())
                return true;
            if(b->getPrice() < a->getPrice())
                return false;
            return a->getId() < b->getId();
        }
};

#endif