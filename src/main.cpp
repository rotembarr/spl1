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

    Workout* workout_test    = new Workout(0, "Jump ropes", 90, ANAEROBIC);
    Workout* workout_test1   = new Workout(0, "MMA", 90, MIXED);
    Workout* workout_test2   = new Workout(0, "Running", 90, CARDIO);

    return 0;
}