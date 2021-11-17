CC = g++
CFLAGS = -g -Wall -std=c++11
LFLAGS = -L/usr/lib

BIN = bin
SRC = src
INCLUDE = include


all :  comp

comp : $(BIN)/Action.o $(BIN)/Customer.o $(BIN)/main.o $(BIN)/Studio.o $(BIN)/Trainer.o $(BIN)/Workout.o
	$(CC) -o $(BIN)/studio $(BIN)/Action.o $(BIN)/Customer.o $(BIN)/main.o $(BIN)/Studio.o $(BIN)/Trainer.o $(BIN)/Workout.o $(LFLAGS)

$(BIN)/Action.o : $(SRC)/Action.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o $(BIN)/Action.o $(SRC)/Action.cpp

$(BIN)/Customer.o : $(SRC)/Customer.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o $(BIN)/Customer.o $(SRC)/Customer.cpp

$(BIN)/main.o : $(SRC)/main.cpp 
	$(CC) $(CFLAGS) -c -Iinclude -o $(BIN)/main.o $(SRC)/main.cpp

$(BIN)/Studio.o : $(SRC)/Studio.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o $(BIN)/Studio.o $(SRC)/Studio.cpp

$(BIN)/Trainer.o : $(SRC)/Trainer.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o $(BIN)/Trainer.o $(SRC)/Trainer.cpp

$(BIN)/Workout.o : $(SRC)/Workout.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o $(BIN)/Workout.o $(SRC)/Workout.cpp

clean:
	rm -f bin/*

run : comp
	${BIN}/studio ExmapleInput.txt

mem_check : comp
	valgrind --leak-check=full --show-reachable=yes $(BIN)/studio 
