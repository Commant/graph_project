COM=gcc
WR=-Wall

all:code

code:graph.o build_graph.o path.o main.c
	${COM} ${WR} -o robot graph.o build_graph.o path.o main.c -lm

graph.o: graph.c
	${COM} ${WR} -c graph.c

build_graph.o: build_graph.c
	${COM} ${WR} -c build_graph.c

path.o: path.c
	${COM} ${WR} -c path.c

clean:
	rm *.o

run:code
	./robot

valrun:code
	valgrind ./robot
