#include "Studio.h"
#include <iostream>

using namespace std;

Studio* backup = nullptr;

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

    Workout workout_test    = Workout(0, "Jump ropes", 90, ANAEROBIC);
    Workout workout_test1   = Workout(1, "MMA", 90, MIXED);
    Workout workout_test2   = Workout(2, "Running", 90, CARDIO);

    cout << workout_test.getId() << ":" << workout_test.getName() << ":" << workout_test.getPrice() << ":" << workout_test.getType() << endl;
    cout << workout_test1.getId() << ":" << workout_test1.getName() << ":" << workout_test1.getPrice() << ":" << workout_test1.getType() << endl;
    cout << workout_test2.getId() << ":" << workout_test2.getName() << ":" << workout_test2.getPrice() << ":" << workout_test2.getType() << endl;


    return 0;
}