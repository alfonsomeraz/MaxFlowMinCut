CC=g++
FLAGS=-g -std=c++11

maxflow: main.cpp
	$(CC) $(FLAGS) $^ -o $@ 
graph: graph.cpp
	$(CC) $(FLAGS) $^ -o $@ 
clean:
	rm -f maxflow
