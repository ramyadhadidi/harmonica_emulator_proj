#
#Ramyad Hadidi
#GPU Architecture
#Fall 2015
#

CXX =g++
#CXXFALGS = -Wall -g -fno-omit-frame-pointer
#CXXFLAGS = -Wall -g
CXXFLAGS = -Wall -O3



all: binReader.o instruction.o core.o main.o 
	$(CXX) $(CXXFLAGS)  main.o binReader.o instruction.o core.o -o harp_emulator

main.o: main.cpp globals.h
	$(CXX) -c $(CXXFLAGS) main.cpp

binReader.o: binReader.cpp globals.h
	$(CXX) -c $(CXXFLAGS) binReader.cpp

instruction.o: instruction.cpp globals.h
	$(CXX) -c $(CXXFLAGS) instruction.cpp

core.o: core.cpp globals.h
	$(CXX) -c $(CXXFLAGS) core.cpp

clean:
	rm *o harp_emulator
