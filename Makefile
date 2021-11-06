all : mem_check comp 

comp : 
	g++ -g -Wall -std=c++11 -o studio.o studio.cpp

mem_check : 
	valgrind --leak-check=full --show-reachable=yes studio.h 