all : mem_check Workout.o 

Workout.o : src/Workout.cpp 
	g++ -g -Wall -std=c++11 -o bin/Workout.o src/Workout.cpp

Customer.o : src/Customer.cpp
	g++ -g -Wall -std=c++11 -o bin/Customer.o src/Customer.cpp src/Workout.cpp
	./bin/Customer.o

mem_check : 
	valgrind --leak-check=full --show-reachable=yes studio.h 