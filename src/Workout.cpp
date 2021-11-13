#include "Workout.h"

//  Basic functions
Workout::Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type):
    id(w_id), name(w_name), price(w_price), type(w_type){}

Workout::Workout(const Workout& other): 
    id(other.getId()), name(other.getName()), price(other.getPrice()), type(other.getType()){}

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
