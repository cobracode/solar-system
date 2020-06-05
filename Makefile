# Makefile for MyApp

# Variables
CXXFLAGS = -march=native -O2 -pipe -fomit-frame-pointer
CXX	= g++
COMPILE = $(CXX) $(CXXFLAGS)
APPNAME	= MyApp.lnx64
INC = ./inc
NEDTRIES = $(INC)/nedtries
SE = $(INC)/SwissEphemerisStatic
SRC = ./src

MyDate.o : $(SRC)/MyDate.cpp
	$(COMPILE) -o MyDate.o -I$(INC) $(SRC)/MyDate.cpp

Logger.o : $(SRC)/Logger.cpp
	$(COMPILE) -o Logger.o -I$(INC) $(SRC)/Logger.cpp

main.o : $(SRC)/main.cpp
	$(COMPILE) -o main.o -I$(INC) -I$(NEDTRIES) -I$(SE) $(SRC)/main.cpp

Body.o : $(SRC)/Body.cpp
	$(COMPILE) -o Body.o -I$(INC) $(SRC)/Body.cpp
