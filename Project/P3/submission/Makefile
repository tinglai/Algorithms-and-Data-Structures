PATH := /usr/um/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64
LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64

FLAGS = -Wall -Wextra -pedantic -Wvla -std=c++11 -O3

debug: FLAGS += -g
debug: all

case: 
	g++ $(FLAGS) -g caseGenerator.cpp source_PR.cpp -o cases

debug_test: FLAGS += -g
debug_test: test

gprof: main.o config.o source_PR.o source_TL.o equity.o equity_m.o equity_ttt.o equity_ttt_m.o
	g++ $(FLAGS) -pg main.o config.o source_PR.o source_TL.o equity.o equity_m.o equity_ttt.o equity_ttt_m.o -o market

main.o: main.cpp
	g++ $(FLAGS) -pg -c main.cpp
config.o: config.cpp
	g++ $(FLAGS) -pg -c config.cpp
source_PR.o: source_PR.cpp
	g++ $(FLAGS) -pg -c source_PR.cpp
source_TL.o: source_TL.cpp
	g++ $(FLAGS) -pg -c source_TL.cpp
equity.o: equity.cpp
	g++ $(FLAGS) -pg -c equity.cpp
equity_m.o: equity_m.cpp
	g++ $(FLAGS) -pg -c equity_m.cpp
equity_ttt.o: equity_ttt.cpp
	g++ $(FLAGS) -pg -c equity_ttt.cpp
equity_ttt_m.o: equity_ttt_m.cpp
	g++ $(FLAGS) -pg -c equity_ttt_m.cpp


test:
	g++ $(FLAGS) -g test.cpp -o test

all: 
	g++ $(FLAGS) main.cpp config.cpp source_PR.cpp source_TL.cpp equity.cpp equity_m.cpp equity_ttt.cpp equity_ttt_m.cpp -o market
# make clean - remove .o files.  You can modify it to remove whatever
clean:
	rm -f *.o market test
