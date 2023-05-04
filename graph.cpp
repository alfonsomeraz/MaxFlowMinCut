/*
Justin Sadler
2023-26-04
C++ program to generate a random directed graph and produce 
CSV file with the list. 
The graph is designed for max flow/min cut problem, so the "weight"
of each edge will be the capacity. 
CSV file: 
source, destination, capacity
Sources:
    https://www.geeksforgeeks.org/how-to-create-a-random-graph-in-c/    
*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <vector>

#if 0
#define LOG(X) std::cout << (X) << std::endl
#else
#define LOG(X) 
#endif

using std::vector;

vector<vector<int>> GenRandomGraphs(unsigned int V, unsigned int E, unsigned int maxCap);
void errorMessage(const char * msg);

int main( int argc, char* argv[] ) {

    std::ofstream myfile;
    const char * filename = "example.csv";
    unsigned long numberOfNodes;
    unsigned long maxEdges;
    unsigned long minEdges;
    unsigned long numberOfEdges;
    unsigned long maxCapacity;
    vector<vector<int>> edgeList;

    if(argc < 4) {
        errorMessage("ERROR: Insufficient number of arguments");
        exit(-1);
    }

    if((numberOfNodes = strtoul(argv[1], NULL, 10)) == 0) {
	errorMessage("ERROR: Could not extract the number of nodes from command line arguments" );
        exit(-1);
    }

    if(numberOfNodes <= 2) {
	errorMessage("Error: Less than 3 nodes in graph. Problem is trivial");
	exit(-1);
    }

    if(strcmp(argv[2], "dense") == 0) {
        maxEdges = numberOfNodes * (numberOfNodes - 1) / 2;
        minEdges = maxEdges / 2;
    } else if(strcmp(argv[2], "sparse") == 0) {
        maxEdges = numberOfNodes * (numberOfNodes - 1) / 4;
        minEdges = numberOfNodes - 1;
    } else {
	errorMessage("ERROR: incorrect option for 2nd command line arguement" );
        exit(-1);
    }

    srand(time(NULL));
    numberOfEdges = (rand() % (maxEdges - minEdges)) + minEdges;

    if((maxCapacity = strtoul(argv[3], NULL, 10)) == 0) {
	errorMessage("ERROR: Could not extract max capacity from command line arguments");
        exit(-1);
    }

    if(argc > 5) {
		filename = argv[4];
    }

    edgeList = GenRandomGraphs(numberOfNodes, numberOfEdges, maxCapacity);

    myfile.open(filename);

    myfile << "source,destination,capacity\n";
    for(vector<int>& edge : edgeList) {
        myfile << edge[0] << ',' << edge[1] << ',' << edge[2] << '\n';
    }
    myfile.close();
    return 0;

}

// C++ code to implement the approach
  
// Function to generate random graph
// Assumes V > 2 and E > V
vector<vector<int>> GenRandomGraphs(unsigned int V, unsigned int E, unsigned int maxCap)
{
    
    int i, j, k;
    // Edge list
    vector<vector<int>> edges(E, vector<int> (3, 0));
    i = 0;
    int source = 0;
    int sink = V - 1;

    srand(time(NULL));
    
	LOG("Intermediary nodes" );
  
    // Assign random values to the number
    // Intermediary edges 
    while (i < (E *.75) ) {
    initEdge1:
	
        edges[i][0] = (rand() % (V - 2)) + 1;
        edges[i][1] = (rand() % (V - 2)) + 1;
  
        // Print the connections of each
        // vertex, irrespective of the
        // direction.
        if(edges[i][0] == edges[i][1]) { // self-loop
            goto initEdge1;
        } 
        for (j = 0; j < i; j++) {
            if ((edges[i][0] == edges[j][0] && edges[i][1] == edges[j][1]) // edge is a duplicate
                || (edges[i][0] == edges[j][1] && edges[i][1] == edges[j][0])) { // there is already an edge between i and j
                    goto initEdge1;
                }
        }
        edges[i][2] = (rand() % (maxCap - 1)) + 1;
        i++;
    }

	k = i;
	LOG("Source edges");
	// Source edges:
	while (i < (E * .875)) {
	initEdge2:
		edges[i][0] = source;
		edges[i][1] = (rand() % (V - 1)) + 1;

		for (j = k; j < i; j++) {
			if ( edges[i][1] == edges[j][1]) { // edge is a duplicat
				LOG("Dup 2--");
				LOG(i);
				LOG(j);
				goto initEdge2;
			}
		}
		edges[i][2] = (rand() % (maxCap - 1)) + 1;
		i++;
	}


	LOG("Sink edges");
	k = i;
	// Destination edges:
	while (i < E) {
        initEdge3:
        edges[i][0] = (rand() % (V - 1));
        edges[i][1] = sink;
  
        for (j = k; j < i; j++) {
            if ( edges[i][0] == edges[j][0]) { // edge is a duplicate
		    LOG("Dup 3");
                    goto initEdge3;
                }
        }
        edges[i][2] = (rand() % (maxCap - 1)) + 1;
        i++;
	}

    return edges;
}

void errorMessage(const char * msg) {
    std::cerr << msg << std::endl;
    std::cerr << "[Format]: ./graph [No. of nodes] [sparse|dense] [Max Capacity] [Filename (default is example.csv)]" << std::endl;
}
