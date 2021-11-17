#include "Customer.h"


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
    return (this->getId() + " " + this->getName());  
}
const std::string SweatyCustomer::customer_type(){
    return "swt";
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
std::string CheapCustomer::toString() const {
    return (this->getId() + " " + this->getName());
}
const std::string CheapCustomer::customer_type(){
    return "chp";
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
    std::sort(anaerobic_workouts.begin(), anaerobic_workouts.end());
    std::vector<int> result = std::vector<int>();
    for(size_t i = 0; i < anaerobic_workouts.size(); i++){
        result.push_back(anaerobic_workouts[i]->getId());
    }
    return result;
}
std::string HeavyMuscleCustomer::toString() const {
    return (this->getId() + " " + this->getName());
}
const std::string HeavyMuscleCustomer::customer_type(){
    return "mcl";
}



//  Full Body Customer
FullBodyCustomer::FullBodyCustomer(std::string name, int id): Customer(name, id){
}
std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options){
      int chpCardioId = -1;
    int chpCardioPrice = std::numeric_limits<int>::max();
    int expMixId = -1;
    int expMixPrice = std::numeric_limits<int>::min();
    int chpAnerId = -1;
    int chpAnerPrice = std::numeric_limits<int>::max();
    std::vector<int> ord;

    // Walk all options by appearence order and search workouts as described above.
    for (std::vector<Workout>::size_type i = 0; i != workout_options.size(); i++) {
        if ((workout_options[i].getType() == WorkoutType::CARDIO) & (workout_options[i].getPrice() < chpCardioPrice)) {
            chpCardioPrice = workout_options[i].getPrice();
            chpCardioId = workout_options[i].getId();
        }
        else if ((workout_options[i].getType() == WorkoutType::MIXED) & (workout_options[i].getPrice() > expMixPrice)) {
            expMixPrice = workout_options[i].getPrice();
            expMixId = workout_options[i].getId();
        }
        else if ((workout_options[i].getType() == WorkoutType::ANAEROBIC) & (workout_options[i].getPrice() < chpAnerPrice)) {
            chpAnerPrice = workout_options[i].getPrice();
            chpAnerId = workout_options[i].getId(); 
        }
    }

    if (!((chpCardioId == -1) | (expMixId == -1) | (chpAnerId == -1))) {
        ord.push_back(chpCardioId);
        ord.push_back(expMixId);
        ord.push_back(chpAnerId);
    }

    return ord; 
}
std::string FullBodyCustomer::toString() const{
	return (this->getId() + " " + this->getName());    
}
const std::string FullBodyCustomer::customer_type(){
    return "fbd";
}
