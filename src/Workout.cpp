#include "../include/Workout.h"

//  Basic functions
Workout::Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type):
    id(w_id), 
    name(w_name), 
    price(w_price), 
    type(w_type) {
}

Workout::Workout(const Workout &other): 
    Workout(other.id, other.name, other.price, other.type) {

}

// bool priceComparator(Workout& a, Workout& b) {
//     return (a.getPrice() < b.getPrice());
// }

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

std::string Workout::toString() const {
    std::string s = ("Workout: id=" + std::to_string(id) + ", name=" + name + ", type=" + std::to_string(type) + ", price=" +std::to_string(price));
    return s;
}