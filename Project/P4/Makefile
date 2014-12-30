PATH := /usr/um/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64
LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64

FLAGS = -Wall -Wextra -pedantic -Wvla -std=c++11 -O3

debug: FLAGS += -g
debug: all

case: 
	g++ $(FLAGS) caseGen.cpp -o cases

debug_test: FLAGS += -g
debug_test: test

gprof: main.o config.o mst.o fastTSP.o optTSP.o
	g++ $(FLAGS) -pg main.o config.o mst.o fastTSP.o optTSP.o -o base

main.o: main.cpp
	g++ $(FLAGS) -pg -c main.cpp
config.o: config.cpp
	g++ $(FLAGS) -pg -c config.cpp
mst.o: mst.cpp
	g++ $(FLAGS) -pg -c mst.cpp
fastTSP.o: fastTSP.cpp
	g++ $(FLAGS) -pg -c fastTSP.cpp
optTSP.o: optTSP.cpp
	g++ $(FLAGS) -pg -c optTSP.cpp


test:
	g++ $(FLAGS) -g test.cpp -o test

all: 
	g++ $(FLAGS) main.cpp config.cpp mst.cpp fastTSP.cpp optTSP.cpp -o base
# make clean - remove .o files.  You can modify it to remove whatever
clean:
	rm -f *.o base test
