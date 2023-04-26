CC=g++

maxflow: main.cpp
	$(CC) $^ -o $@ 
clean:
	rm -f maxflow