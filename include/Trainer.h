#ifndef TRAINER_H_
#define TRAINER_H_

#include <vector>
#include "Customer.h"
#include "Workout.h"

typedef std::pair<int, Workout> OrderPair;

class Trainer{
public:
    Trainer(int t_capacity);
    Trainer(int t_capacity, int t_id);

    // Rule of 5.
    Trainer(const Trainer& other);
    Trainer(Trainer&& other);
    Trainer& operator=(const Trainer& other);
    Trainer& operator=(Trainer&& other);
    virtual ~Trainer();

    // Functions.
    int getCapacity() const;
    int getId() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    void order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options);
    void openTrainer();
    void closeTrainer();
    int getSalary();
    bool isOpen();
    std::string toString() const;
protected:
    void delCustomerOrders(int id);
    void clear();
private:
    int capacity;
    int salary;
    int id;
    bool open;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order for the trainer - (customer_id, Workout)
};


#endif
