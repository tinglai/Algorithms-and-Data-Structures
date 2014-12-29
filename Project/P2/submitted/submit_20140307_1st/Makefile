PATH := /usr/um/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64
LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64

FLAGS = -Wall -Wextra -pedantic -Wvla -std=c++11

release: FLAGS += -O3
release: all

debug: FLAGS += -g
debug: all

test:
	g++ $(FLAGS) test.cpp -o test

all: 
	g++ $(FLAGS) main.cpp config.cpp gameInfo.cpp readin.cpp zombie.cpp verbose.cpp -o rotld
# make clean - remove .o files.  You can modify it to remove whatever
clean:
	rm -f *.o rotld test
