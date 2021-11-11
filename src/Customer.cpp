#include "../include/Customer.h"


///////////////////// Customer ///////////////////////////////
Customer::Customer(std::string c_name, int c_id):
    name(c_name),
    id(c_id) {        
}

std::string Customer::getName() const {
    return this->name;
}


int Customer::getId() const {
    return this->id;
}

///////////////////// SweatyCustomer ///////////////////////////////
SweatyCustomer::SweatyCustomer(std::string name, int id): 
    Customer(name, id) {
}

std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> ord;

    // Walk all options by appearence order and add all cardio workouts.
    for (Workout workout : workout_options) {
        if(workout.getType() == WorkoutType::CARDIO) {
            ord.push_back(workout.getId());
        }
    }

    return ord; // TODO - maybe retiurn differntly
}


std::string SweatyCustomer::toString() const {
    return "SweatyCustomer";// TODO
}

///////////////////// CheapCustomer ///////////////////////////////
CheapCustomer::CheapCustomer(std::string name, int id): 
    Customer(name, id) {
}

std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options) {
    int chpVal = std::numeric_limits<int>::max();
    int chpId = -1;
    std::vector<int> ord;

    // find to cheapest workout.
    for (Workout workout : workout_options) {
        if(workout.getPrice() < chpVal) {
            chpVal = workout.getPrice();
            chpId  = workout.getId();
        }
    }

    ord.push_back(chpId);
    return ord; // TODO - maybe return differntly
}


std::string CheapCustomer::toString() const {
    return "CheapCustomer";// TODO
}

///////////////////// HeavyMuscleCustomer ///////////////////////////////
HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id): 
    Customer(name, id) {
}


std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<idAndPrice> anerWo;
    std::vector<int> idVec;

    // Walk all options by appearence order and add all the ANAEROBIC workouts.
    for (Workout workout : workout_options) {

        if(workout.getType() == WorkoutType::ANAEROBIC) {
            // std::cout << workout.getId() << std::endl;
            idAndPrice inp(workout.getId(),workout.getPrice());
            anerWo.push_back(inp);
        }
    
    }

    // Sort Anerobic workout by their price
    std::sort(anerWo.begin(), anerWo.end(), 
        [](const idAndPrice a, const idAndPrice b) {
            return (std::get<1>(a) > std::get<1>(b));
        }
    );

    // Return their IDs.
    for (idAndPrice inp : anerWo) {
        idVec.push_back(std::get<0>(inp));
    }
    return idVec; // TODO - maybe return differntly
}


std::string HeavyMuscleCustomer::toString() const {
    return "HeavyMuscleCustomer";    // TODO
}

///////////////////// FullBodyCustomer ///////////////////////////////
FullBodyCustomer::FullBodyCustomer(std::string name, int id): 
    Customer(name, id) {
}

std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options) {
    int chpCardioId = -1;
    int chpCardioPrice = std::numeric_limits<int>::max();
    int expMixId = -1;
    int expMixPrice = std::numeric_limits<int>::min();
    int chpAnerId = -1;
    int chpAnerPrice = std::numeric_limits<int>::max();
    std::vector<int> ord;

    // Walk all options by appearence order and search workouts as described above.
    for (Workout workout : workout_options) {
        if ((workout.getType() == WorkoutType::CARDIO) & (workout.getPrice() < chpCardioPrice)) {
            chpCardioPrice = workout.getPrice();
            chpCardioId = workout.getId();
        }
        else if ((workout.getType() == WorkoutType::MIXED) & (workout.getPrice() > expMixPrice)) {
            expMixPrice = workout.getPrice();
            expMixId = workout.getId();
        }
        else if ((workout.getType() == WorkoutType::ANAEROBIC) & (workout.getPrice() < chpAnerPrice)) {
            chpAnerPrice = workout.getPrice();
            chpAnerId = workout.getId(); 
        }
    }

    if (!((chpCardioId == -1) | (expMixId == -1) | (chpAnerId == -1))) {
        ord.push_back(chpCardioId);
        ord.push_back(expMixId);
        ord.push_back(chpAnerId);
    }

    return ord; // TODO - maybe return differntly
}


std::string FullBodyCustomer::toString() const {
    return "FullBodyCustomer";    // TODO
}
