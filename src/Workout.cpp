#include "Workout.h"

//  Basic functions
Workout::Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type):
    id(w_id), 
    name(w_name), 
    price(w_price), 
    type(w_type) {
}

Workout::Workout(const Workout &other): 
    Workout(other.getId(), other.getName(), other.getPrice(), other.getType()) {
}

int Workout::getId() const{
    return this->id;
}

std::string Workout::getName() const{
    return this->name;
}

int Workout::getPrice() const{
    return this->price;
}

WorkoutType Workout::getType() const{
    return this->type;
}

bool Workout::operator<(const Workout &b) const{
    if(this->price < b.getPrice())
        return true;
    else if(b.getPrice() < this->price)
        return false;
    else
        return this->id < b.getId();
}

bool Workout::operator>(const Workout &b) const{
    if(this->price > b.getPrice())
        return true;
    else if(b.getPrice() > this->price)
        return false;
    else
        return this->id < b.getId();
}

std::string Workout::toString() const {
    std::string s = (this->name + ", " + Workout::typeToString(type) + ", " + std::to_string(price));
    return s;
}

std::string Workout::typeToString(WorkoutType type) {
    if (type == ANAEROBIC)
        return "Anaerobic";
    else if (type == MIXED)
        return "Mixed";
    else if (type == CARDIO)
        return "Cardio";
    else
        return "Unknown Workout Type";
}

WorkoutType Workout::strToType(std::string &str) {
    if (str.compare("Anaerobic") == 0) {
        return ANAEROBIC;
    }
    else if (str.compare("Mixed") == 0) {
        return MIXED;
    }
    else if (str.compare("Cardio") == 0) {
        return CARDIO;
    }
    else {
       return UNKNOWN;
    }
}
