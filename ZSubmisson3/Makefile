#
#Ramyad Hadidi
#GPU Architecture
#Fall 2015
#

CXX =g++
CXXFALGS = -c -Wall -g


all: binReader.o instruction.o warp.o core.o main.o 
	$(CXX) main.o binReader.o instruction.o warp.o core.o -o harp_emulator

main.o: main.cpp globals.h
	$(CXX) $(CXXFALGS) main.cpp

binReader.o: binReader.cpp globals.h
	$(CXX) $(CXXFALGS) binReader.cpp

instruction.o: instruction.cpp globals.h
	$(CXX) $(CXXFALGS) instruction.cpp

warp.o: warp.cpp globals.h
	$(CXX) $(CXXFALGS) warp.cpp

core.o: core.cpp globals.h
	$(CXX) $(CXXFALGS) core.cpp

clean:
	rm *o harp_emulator