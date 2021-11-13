#include "Customer.h"
#include <iostream>
#include <algorithm>

// Customer
Customer::Customer(std::string c_name, int c_id): name(c_name), id(c_id){}
std::string Customer::getName() const{ return this->name; }
5int Customer::getId() const { return this->id; }


// Sweaty Customer
SweatyCustomer::SweatyCustomer(std::string name, int id): Customer(name, id){
    this->workout_strategy = std::vector<const Workout*>();
}
std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> id_vector = std::vector<int>();
    for(size_t i = 0; i < workout_options.size(); i++){
        if(workout_options[i].getType() == CARDIO){
            id_vector.push_back(workout_options[i].getId());
            this->workout_strategy.push_back(&workout_options[i]);
        }
    }
    return id_vector;
}
std::string SweatyCustomer::toString() const {
    std::string result = std::string();
    for(const Workout* wo_option : this->workout_strategy){
        result += wo_option->getName() + "(" + std::to_string(wo_option->getId()) + "), ";
    }
    return result;
}



//  Cheap Customer
CheapCustomer::CheapCustomer(std::string name, int id): Customer(name, id){
    this->workout_strategy = nullptr;
}
std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options){
    const Workout* cheapest = &workout_options[0];
    for(size_t i = 0; i < workout_options.size(); i++){
        if(workout_options[i] < *cheapest)
            cheapest = &workout_options[i];
    }
    this->workout_strategy = cheapest;
    return std::vector<int>(cheapest->getId());
}
std::string CheapCustomer::toString() const{
    return this->workout_strategy->getName() + "(" + std::to_string(this->workout_strategy->getId()) + "), ";
}



//  Heavy Muscle Customer
HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id): Customer(name, id){
    this->workout_strategy = std::vector<const Workout*>();
}
std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options){   
    for(size_t i = 0; i < workout_options.size(); i++){
        if(workout_options.at(i).getType() == ANAEROBIC){
            this->workout_strategy.push_back(&workout_options.at(i));
        }
    }
    std::sort(this->workout_strategy.begin(), this->workout_strategy.end(), Workout_comp_high_to_low());
    std::vector<int> result = std::vector<int>();
    for(const Workout* wo_option : this->workout_strategy){
        result.push_back(wo_option->getId());
    }
    return result;
}
std::string HeavyMuscleCustomer::toString() const{
    std::string result = "";
    for(const Workout* wo_option : this->workout_strategy){
        result += wo_option->getName() + "(" + std::to_string(wo_option->getId()) + "), ";
    }
    return result;
}




//  Full Body Customer
FullBodyCustomer::FullBodyCustomer(std::string name, int id): Customer(name, id){
    this->workout_strategy = std::vector<const Workout*>();
}
std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options){
    
    std::vector<int> result = std::vector<int>();

    //  Cheapest cardio
    const Workout* wo_pointer = nullptr;
    for(size_t i = 0; i < workout_options.size(); i++){
        if(workout_options[i].getType() == CARDIO){
            if(wo_pointer == nullptr)
                wo_pointer = &workout_options[i];
            else {
                if(workout_options[i] < *wo_pointer){
                    wo_pointer = &workout_options[i];
                }
            }
        }
    }
    this->workout_strategy.push_back(wo_pointer);
    result.push_back(wo_pointer->getId());

    //  Most expensive Mix
    wo_pointer = nullptr;
    for(size_t i = 0; i < workout_options.size(); i++){
        if(workout_options[i].getType() == MIXED){
            if(wo_pointer == nullptr)
                wo_pointer = &workout_options[i];
            else {
                if(workout_options[i] > *wo_pointer){
                    wo_pointer = &workout_options[i];
                }
            }
        }
    }
    this->workout_strategy.push_back(wo_pointer);
    result.push_back(wo_pointer->getId());

    //  Cheapest anaerobic
    wo_pointer = nullptr;
    for(size_t i = 0; i < workout_options.size(); i++){
        if(workout_options[i].getType() == ANAEROBIC){
            if(wo_pointer == nullptr)
                wo_pointer = &workout_options[i];
            else {
                if(workout_options[i] < *wo_pointer){
                    wo_pointer = &workout_options[i];
                }
            }
        }
    }
    this->workout_strategy.push_back(wo_pointer);
    result.push_back(wo_pointer->getId());

    return result;
}
std::string FullBodyCustomer::toString() const{
    std::string result = std::string();
    for(const Workout* wo_option : this->workout_strategy){
        result += wo_option->getName() + "(" + std::to_string(wo_option->getId()) + "), ";
    }
    return result;
}
