PATH := /usr/um/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64
LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64

FLAGS = -Wall -Wextra -pedantic -Wvla -std=c++11

release: FLAGS += -O3
release: all

debug: FLAGS += -g
debug: all

debug_test: FLAGS += -g
debug_test: test

gprof: main.o config.o gameInfo.o readin.o zombie.o verbose.o
	g++ $(FLAGS) -pg main.o config.o gameInfo.o readin.o zombie.o verbose.o -o rotld

main.o: main.cpp
	g++ $(FLAGS) -pg -c main.cpp
config.o: config.cpp
	g++ $(FLAGS) -pg -c config.cpp
gameInfo.o: gameInfo.cpp
	g++ $(FLAGS) -pg -c gameInfo.cpp
readin.o: readin.cpp
	g++ $(FLAGS) -pg -c readin.cpp
zombie.o: zombie.cpp
	g++ $(FLAGS) -pg -c zombie.cpp
verbose.o: verbose.cpp
	g++ $(FLAGS) -pg -c verbose.cpp

test:
	g++ $(FLAGS) -g test.cpp -o test

all: 
	g++ $(FLAGS) main.cpp problem4.cpp -o p4
# make clean - remove .o files.  You can modify it to remove whatever
clean:
	rm -f *.o p4 test
