#include "Customer.h"
#include <iostream>
#include <algorithm>

// Customer
Customer::Customer(std::string c_name, int c_id): name(c_name), id(c_id){}
std::string Customer::getName() const{ return this->name; }
int Customer::getId() const { return this->id; }


// Sweaty Customer
SweatyCustomer::SweatyCustomer(std::string name, int id): Customer(name, id){
}
std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> id_vector = std::vector<int>();
    for(size_t i = 0; i < workout_options.size(); i++){
        if(workout_options[i].getType() == CARDIO){
            id_vector.push_back(workout_options[i].getId());
        }
    }
    return id_vector;
}
std::string SweatyCustomer::toString() const {
    return this->getName() + "(" + std::to_string(this->getId()) + "):";;
}



//  Cheap Customer
CheapCustomer::CheapCustomer(std::string name, int id): Customer(name, id){
}
std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options){
    const Workout* cheapest = &workout_options[0];
    for(size_t i = 0; i < workout_options.size(); i++){
        if(workout_options[i] < *cheapest)
            cheapest = &workout_options[i];
    }
    return {cheapest->getId()};
}
std::string CheapCustomer::toString() const{
    return this->getName() + "(" + std::to_string(this->getId()) + ")";
}



//  Heavy Muscle Customer
HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id): Customer(name, id){
}
std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<const Workout*> anaerobic_workouts = std::vector<const Workout*>();  
    for(size_t i = 0; i < workout_options.size(); i++){
        if(workout_options.at(i).getType() == ANAEROBIC){
            anaerobic_workouts.push_back(&workout_options.at(i));
        }
    }
    std::sort(anaerobic_workouts.begin(), anaerobic_workouts.end(), Workout_comp_high_to_low());
    std::vector<int> result = std::vector<int>();
    for(size_t i = 0; i < anaerobic_workouts.size(); i++){
        result.push_back(anaerobic_workouts[i]->getId());
    }
    return result;
}
std::string HeavyMuscleCustomer::toString() const{
    return this->getName() + "(" + std::to_string(this->getId()) + "):";
}




//  Full Body Customer
FullBodyCustomer::FullBodyCustomer(std::string name, int id): Customer(name, id){
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
    result.push_back(wo_pointer->getId());

    return result;
}
std::string FullBodyCustomer::toString() const{
    return this->getName() + "(" + std::to_string(this->getId()) + "):";
}
