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
    for (std::vector<Workout>::size_type i = 0; i != workout_options.size(); i++) {
        if(workout_options[i].getType() == WorkoutType::CARDIO) {
            ord.push_back(workout_options[i].getId());
        }
    }

    return ord; 
}


std::string SweatyCustomer::toString() const {
    return (this->getId() + " " + this->getName());  
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
    for (std::vector<Workout>::size_type i = 0; i != workout_options.size(); i++) {

        if(workout_options[i].getPrice() < chpVal) {
            chpVal = workout_options[i].getPrice();
            chpId  = workout_options[i].getId();
        }
    }

    ord.push_back(chpId);
    
    return ord;
}


std::string CheapCustomer::toString() const {
    return (this->getId() + " " + this->getName());
}

///////////////////// HeavyMuscleCustomer ///////////////////////////////
HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id): 
    Customer(name, id) {
}


std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<idAndPrice> anerWo;
    std::vector<int> idVec;

    // Walk all options by appearence order and add all the ANAEROBIC workouts.
    for (std::vector<Workout>::size_type i = 0; i != workout_options.size(); i++) {

        if(workout_options[i].getType() == WorkoutType::ANAEROBIC) {
            idAndPrice inp(workout_options[i].getId(),workout_options[i].getPrice());
            anerWo.push_back(inp);
        }
    
    }

    // Sort Anerobic workout by their price.
    std::sort(anerWo.begin(), anerWo.end(), 
        [](const idAndPrice a, const idAndPrice b) {
            return (std::get<1>(a) > std::get<1>(b));
        }
    );

    // Return their IDs.
    for (idAndPrice inp : anerWo) {
        idVec.push_back(std::get<0>(inp));
    }

    return idVec;
}


std::string HeavyMuscleCustomer::toString() const {
    return (this->getId() + " " + this->getName());
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


std::string FullBodyCustomer::toString() const {
    return (this->getId() + " " + this->getName());    
}


#include <stdlib.h>
int testCustomer () {
    Customer* c = nullptr;
    std::vector<Workout> wo_vec;
    std::vector<int> out;

    for (int i = 0; i < 10; ++i)
    {
        int price = rand() % 100;
        WorkoutType type = (WorkoutType)((rand() % 7)%3);
        Workout wo (i, "aaa",price,type);
        std::cout << "Workout index " << i << " = " << wo.toString() << std::endl;
        wo_vec.push_back(wo);
    }

    std::cout << "Sweat" << std::endl;
    c = new SweatyCustomer("dan", 7);
    out = c->order(wo_vec);
    for (int i : out) {
        std::cout << i << std::endl;    
    }

    std::cout << "Cheap" << std::endl;
    c = new CheapCustomer("dan", 7);
    out = c->order(wo_vec);
    for (int i : out) {
        std::cout << i << std::endl;    
    }

    std::cout << "HeavyMuscle" << std::endl;
    c = new HeavyMuscleCustomer("dan", 7);
    out = c->order(wo_vec);
    for (int i : out) {
        std::cout << i << std::endl;    
    }

    std::cout << "FullBody" << std::endl;
    c = new FullBodyCustomer("dan", 7);
    out = c->order(wo_vec);
    for (int i : out) {
        std::cout << i << std::endl;    
    }
    
    return 0;
}

// int main(int argc, char const *argv[])
// {
//     return testCustomer();
// }