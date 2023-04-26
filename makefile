CC=g++
FLAGS=-g

maxflow: main.cpp
	$(CC) $(FLAGS) $^ -o $@ 
graph: graph.cpp
	$(CC) $(FLAGS) $^ -o $@ 
clean:
	rm -f maxflow
