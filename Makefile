CXX =g++
CXXFALGS = -c -Wall

all: util.o instruction.o warp.o core.o main.o 
	$(CXX) main.o util.o instruction.o warp.o core.o -o harp_emulator

main.o: main.cpp globals.h
	$(CXX) $(CXXFALGS) main.cpp

util.o: util.cpp globals.h
	$(CXX) $(CXXFALGS) util.cpp

instruction.o: instruction.cpp globals.h
	$(CXX) $(CXXFALGS) instruction.cpp

warp.o: warp.cpp globals.h
	$(CXX) $(CXXFALGS) warp.cpp

core.h: core.cpp globals.h
	$(CXX) $(CXXFALGS) core.cpp

clean:
	rm *o harp_emulator