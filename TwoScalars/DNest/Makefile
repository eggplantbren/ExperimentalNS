CFLAGS = -O2 -Wall -Wextra -ansi -pedantic
LIBS =  -ldnest3 -lgsl -lgslcblas -lboost_system -lboost_thread

default:
	g++ $(CFLAGS) -c *.cpp
	g++ -o main main.o MyModel.o $(LIBS)
	g++ -o run_walker run_walker.o MyModel.o $(LIBS)
	rm -f *.o

