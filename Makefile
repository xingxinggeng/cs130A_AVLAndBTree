#Makefile for cs130A project01
all: main

main: main.cpp BTree.cpp AVL.cpp 
	g++ -g -std=c++11 -o main main.cpp BTree.cpp AVL.cpp  -lstdc++fs

clean:
	rm -f main
