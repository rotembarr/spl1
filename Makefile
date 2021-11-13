all : mem_check Workout.o 

Workout.o : 
	g++ -g -Wall -std=c++11 -o bin/Workout.o src/Workout.cpp
	./bin/Workout.o

Customer.o :
	g++ -g -Wall -std=c++11 -o bin/Customer.o src/Customer.cpp src/Workout.cpp
	./bin/Customer.o

Trainer.o :
	g++ -g -Wall -std=c++11 -o bin/Trainer.o src/Trainer.cpp src/Customer.cpp src/Workout.cpp
	./bin/Trainer.o

Studio.o : 
	g++ -g -Wall -std=c++11 -o bin/Trainer.o src/Studio.cpp src/Trainer.cpp src/Customer.cpp src/Workout.cpp
	./bin/Studio.o

main.o :
	g++ -g -Wall -std=c++11 -o bin/main.o src/main.cpp src/Studio.cpp src/Trainer.cpp src/Customer.cpp src/Workout.cpp

run : main.o
	./bin/main.o /home/rotem/Downloads/ExmapleInput.txt
mem_check : 
	valgrind --leak-check=full --show-reachable=yes studio.h 