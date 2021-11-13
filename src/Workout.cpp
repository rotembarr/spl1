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
    if (str == "Anaerobic") {
        return ANAEROBIC;
    }
    else if (str == "Mixed") {
        return MIXED;
    }
    else if (str == "Cardio") {
        return CARDIO;
    }
    else {
       return UNKNOWN;
    }
}

// Workout& Workout::operator=(const Workout& other) {
//     std::cout << "asasas" << std::endl;

//     if (this != &other) {
//         // id=other.getId();
//         // name=other.getName();
//         // price=other.getPrice();
//         // type=other.getType();
//     }
//     return (*this);
// }


#include <vector>
int testWorkout () {
    Workout a(0,"a",0,CARDIO);
    Workout b(1,"b",1,MIXED);

    std::cout << a.toString() << std::endl;
    std::cout << b.toString() << std::endl;

//    b = a;

    std::cout << a.toString() << std::endl;
    std::cout << b.toString() << std::endl;

    std::cout << "part 2" << std::endl;
    std::vector<Workout> vec;
    vec.push_back(a);
    std::cout << std::endl;

    std::cout << a.getId() << std::endl;
    std::cout << vec[0].getId() << std::endl;
    // for (Workout workout : vec) {
    for (std::vector<Workout>::size_type i = 0; i!=vec.size(); i++) {
        std::cout << vec[i].getId() << std::endl;
    }

    return 0;
}