#makefile for CSCI 2270 Final Project
#Addition to Thompson_CSCI2270_FinalProject

OBJS = Graph.o 
CC = g++
CPPFLAGS = -Wall -Wextra -std=c++11
PROG = carTrip


$(PROG): $(OBJS)
	$(CC) $(CPPFLAGS) -o $(PROG) $(OBJS) main.cpp

Graph.o: Graph.h Graph.cpp
	$(CC) $(CPPFLAGS) -c Graph.cpp

clean:
	$(RM)  $(PROG) $(OBJS)