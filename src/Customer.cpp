#include <Customer.h>

// Customer
Customer::Customer(std::string c_name, int c_id): name(c_name), id(c_id){}
std::string Customer::getName() const{ return this->name; }
int Customer::getId() const { return this->id; }


// Sweaty Customer
SweatyCustomer::SweatyCustomer(std::string name, int id): Customer(name, id){
    this->workout_strategy = std::vector<Workout>();
}
std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> workout_ids = std::vector<int>();
    for(Workout workout_option : workout_options){
        if(workout_option.getType() == CARDIO){
            this->workout_strategy.push_back(workout_option);
            workout_ids.push_back(workout_option.getId());
        }
        return workout_ids;
    }
}
std::string SweatyCustomer::toString() const {
    std::string result = std::string();
    for(Workout wo_option : this->workout_strategy){
        result += wo_option.getName() + " ";
    }
    return result;
}



//  Cheap Customer
CheapCustomer::CheapCustomer(std::string name, int id): Customer(name, id){
    this->workout_strategy = -1;
}
std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options){
    const Workout* cheapest = &workout_options[0];
    for(Workout wo_option : workout_options){
        if(wo_option < *cheapest)
            cheapest = &wo_option;
    }
    this->workout_strategy = cheapest->getId();
    return std::vector<int>(cheapest->getId());
}
std::string CheapCustomer::toString() const{
    return std::to_string(this->workout_strategy);
}



//  Heavy Muscle Customer
HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id): Customer(name, id){
    std::vector<Workout> workout_strategy = std::vector<Workout>();
}
std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> result = std::vector<int>();
    return result;
}
std::string HeavyMuscleCustomer::toString() const{
    return "Not implemented yet";
}


//  Full Body Customer
FullBodyCustomer::FullBodyCustomer(std::string name, int id): Customer(name, id){
    this->workout_strategy = std::vector<Workout>(3);
}
std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options){
    
    std::vector<int> result = std::vector<int>();

    //  Cheapest cardio
    const Workout* wo_pointer = &workout_options[0];
    for(Workout wo_option : workout_options){
        if((wo_option < *wo_pointer) & (wo_option.getType() == CARDIO)){
            wo_pointer = &wo_option;
        }
    }
    this->workout_strategy.push_back(*wo_pointer);
    result[0] = wo_pointer->getId();

    //  Most expensive Mix
    wo_pointer = &workout_options[0];
    for(Workout wo_option : workout_options){
        if((wo_option > *wo_pointer) & (wo_option.getType() == MIXED)){
            wo_pointer = &wo_option;
        }
    }
    this->workout_strategy.push_back(*wo_pointer);
    result[1] = wo_pointer->getId();

    //  Cheapest anaerobic
    wo_pointer = &workout_options[0];
    for(Workout wo_option : workout_options){
        if((wo_option < *wo_pointer) & (wo_option.getType() == ANAEROBIC)){
            wo_pointer = &wo_option;
        }
    }
    this->workout_strategy.push_back(*wo_pointer);
    result[2] = wo_pointer->getId();

    return result;
}
std::string FullBodyCustomer::toString() const{
    return "Not implemented yet";
}