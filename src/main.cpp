#include "Studio.h"
#include <iostream>

using namespace std;

Studio* backup = nullptr;

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

int main(int argc, char** argv){
    // if(argc!=2){
    //     std::cout << "usage: studio <config_path>" << std::endl;
    //     return 0;
    // }
    // string configurationFile = argv[1];
    // Studio studio(configurationFile);
    // studio.start();
    // if(backup!=nullptr){
    // 	delete backup;
    // 	backup = nullptr;
    // }

    Workout* workout_test    = new Workout(0, "Jump ropes", 90, ANAEROBIC);
    Workout* workout_test1   = new Workout(0, "MMA", 90, MIXED);
    Workout* workout_test2   = new Workout(0, "Running", 90, CARDIO);

    return 0;
}