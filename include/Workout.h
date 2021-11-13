#ifndef WORKOUT_H_
#define WORKOUT_H_

#include <string>
#include <iostream>

enum WorkoutType{
    ANAEROBIC, MIXED, CARDIO, NUM_OF_WORKOUT_TYPES, UNKNOWN
};

class Workout{
public:
    Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type);
    Workout(const Workout &other);
    int getId() const;
    std::string getName() const;
    int getPrice() const;
    WorkoutType getType() const;
    std::string toString() const;
    static std::string typeToString(WorkoutType type);
    static WorkoutType strToType(std::string &str);
//    Workout& operator=(const Workout& other);
private:
	const int id;
    const std::string name;
    const int price;
    const WorkoutType type;
};

#endif