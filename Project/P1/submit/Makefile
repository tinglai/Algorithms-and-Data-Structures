PATH := /usr/um/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64
LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64

FLAGS = -Wall -Wextra -pedantic -Wvla -std=c++11 -O3

release: FLAGS += -O3
release: all

debug: FLAGS += -g
debug: all

all: main.o config.o terrainInfo.o route.o out.o
	g++ $(FLAGS) main.o config.o terrainInfo.o route.o out.o -o proj1
main.o: main.cpp
	g++ $(FLAGS) -c main.cpp
config.o: config.cpp
	g++ $(FLAGS) -c config.cpp
terrainInfo.o: terrainInfo.cpp
	g++ $(FLAGS) -c terrainInfo.cpp
route.o: route.cpp
	g++ $(FLAGS) -c route.cpp
out.o: out.cpp
	g++ $(FLAGS) -c out.cpp
# make clean - remove .o files.  You can modify it to remove whatever
clean:
	rm -f *.o proj1
