#include "Studio.h"
#include <iostream>

// using namespace std;

Studio* backup = nullptr;


int testTrainer() {
    Trainer* trainer = new Trainer(7, 0);
    std::vector<Workout> workout_options;

    // Workout options.
    for (int i = 0; i < 5; i++){
        workout_options.push_back(Workout(i, "wo"+std::to_string(i), rand() % 100, static_cast<WorkoutType>(rand()%6) ));
    }

    // Trainer 
    std::cout << "///////////////////// trainer creatin" << std::endl;
    trainer->addCustomer(new CheapCustomer("gev", 0));
    trainer->order(0,{0,2}, workout_options);
    std::cout << trainer->toString() << std::endl;

    // Copy constructor
    std::cout << "///////////////////// copy constructor" << std::endl;
    Trainer *trainer2 = new Trainer(*trainer);
    std::cout << trainer2->toString() << std::endl;
    trainer2->removeCustomer(0);
    std::cout << trainer->toString() << std::endl;
    std::cout << trainer2->toString() << std::endl;

    // Move constructor.
    std::cout << "///////////////////// move constructor" << std::endl;
    Trainer *trainer3 = new Trainer(std::move(*trainer));
    std::cout << trainer3->toString() << std::endl;
    std::cout << trainer->toString() << std::endl;

    // copy assignment.
    std::cout << "///////////////////// copy assignment" << std::endl;
    Trainer trainer4(6);
    trainer4 = (*trainer3);
    trainer3->removeCustomer(0);
    std::cout << trainer3->toString() << std::endl;
    std::cout << trainer4.toString() << std::endl;

    // Move assignment operator
    std::cout << "///////////////////// move assignent" << std::endl;
    Trainer trainer5(8);
    trainer5 = std::move(trainer4);
    std::cout << trainer4.toString() << std::endl;
    std::cout << trainer5.toString() << std::endl;


    return 0;
}

int testWorkout() {
    return 0;
}

int main(int argc, char** argv){

    if(argc!=2){
        std::cout << "usage: studio <config_path>" << std::endl;
        return 0;
    }
    std::string configurationFile = argv[1];
    Studio studio(configurationFile);
    studio.start();
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
    return 0;
}



int testChupa() {
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
    fbc2.order(workout_options);
    fbc3.order(workout_options);
    fbc4.order(workout_options);

    std::cout << "swt: " << swt.toString() << std::endl;
    std::cout << "chp: " << chp.toString() << std::endl;
    std::cout << "hmc: " << hmc.toString() << std::endl;
    std::cout << "fbc: " << fbc.toString() << std::endl;

    std::cout << std::endl << std::endl << "Trainer tests" << std::endl;

    Trainer trainer = Trainer(6);
    std::cout << trainer.getCapacity() << std::endl;
    trainer.addCustomer(&swt);
    trainer.addCustomer(&chp);
    trainer.addCustomer(&hmc);
    trainer.addCustomer(&fbc);
    trainer.addCustomer(&fbc2);
    trainer.addCustomer(&fbc3);
    trainer.addCustomer(&fbc4);
    std::vector<Customer*> customers = trainer.getCustomers();

    //  Test 1:
    std::cout << std::endl << "Customers 1:" << std::endl;
    for(Customer* customer : customers){ std::cout << customer->toString() << std::endl; }
    std::cout << std::endl;
    trainer.removeCustomer(4);
    trainer.removeCustomer(5);
    customers = trainer.getCustomers();
    std::cout << "Remove(5):" << std::endl;
    for(Customer* customer : customers){ std::cout << customer->toString() << std::endl; }
    std::cout << std::endl;
    std::cout << "Get 2:" << std::endl;
    std::cout << trainer.getCustomer(2)->getName() << "(" << trainer.getCustomer(2)->getId() << ")" << std::endl;


    std::cout << std::endl;
    std::cout << "Order 0:" << std::endl;
    for(size_t i = 0; i < trainer.getCustomers().size(); i++){
        std::vector<int> customer_order = trainer.getCustomer(i)->order(workout_options);
        trainer.order(i, customer_order, workout_options);
    }
    for(OrderPair order_pair : trainer.getOrders()){
        std::cout << "(" + std::to_string(order_pair.first) + "): " + order_pair.second.getName(); 
    }
    //trainer.order
    trainer.openTrainer();
    std::cout << trainer.isOpen() << std::endl;
    trainer.closeTrainer();
    std::cout << trainer.isOpen() << std::endl;
    std::cout << trainer.getSalary() << std::endl;

    return 0;
}
