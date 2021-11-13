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

    Workout workout_0   = Workout(0, "Yoga", 90, ANAEROBIC);
    Workout workout_1   = Workout(1, "Pilates", 110, ANAEROBIC);
    Workout workout_2   = Workout(2, "Spinning", 120, MIXED);
    Workout workout_3   = Workout(3, "Zumba", 100, CARDIO);
    Workout workout_4   = Workout(4, "Rope Jumps", 70, CARDIO);
    Workout workout_5   = Workout(5, "CrossFit", 140, MIXED);


    const std::vector<Workout> workout_options = {workout_0, workout_1, workout_2, workout_3, workout_4, workout_5}; 


    SweatyCustomer swt = SweatyCustomer("shalom", 0);
    CheapCustomer chp = CheapCustomer("dan", 1);
    HeavyMuscleCustomer hmc = HeavyMuscleCustomer("alice", 2);
    FullBodyCustomer fbc = FullBodyCustomer("bob", 3);
    FullBodyCustomer fbc2 = FullBodyCustomer("bob2", 4);
    FullBodyCustomer fbc3 = FullBodyCustomer("bob3", 5);
    FullBodyCustomer fbc4 = FullBodyCustomer("bob4", 6);

    swt.order(workout_options);
    chp.order(workout_options);
    hmc.order(workout_options);
    fbc.order(workout_options);

    cout << "swt: " << swt.toString() << endl;
    cout << "chp: " << chp.toString() << endl;
    cout << "hmc: " << hmc.toString() << endl;
    cout << "fbc: " << fbc.toString() << endl;

    cout << endl << endl << "Trainer tests" << endl;

    Trainer trainer = Trainer(6);
    cout << trainer.getCapacity() << endl;
    trainer.addCustomer(&swt);
    trainer.addCustomer(&chp);
    trainer.addCustomer(&hmc);
    trainer.addCustomer(&fbc);
    trainer.addCustomer(&fbc2);
    trainer.addCustomer(&fbc3);
    trainer.addCustomer(&fbc4);
    std::vector<Customer*> customers = trainer.getCustomers();
    for(Customer* customer : customers){ cout << customer->getName() << "(" << customer->getId() << ")" << endl; }
    trainer.removeCustomer(5);
    for(Customer* customer : customers){ cout << customer->getName() << "(" << customer->getId() << ")" << endl; }
    cout << trainer.getCustomer(3)->getName() << "(" << trainer.getCustomer(3)->getId() << ")" << endl;
    //trainer.getOrders()
    //trainer.order
    trainer.openTrainer();
    cout << trainer.isOpen() << endl;
    trainer.closeTrainer();
    cout << trainer.isOpen() << endl;
    cout << trainer.getSalary() << endl;

    return 0;
}