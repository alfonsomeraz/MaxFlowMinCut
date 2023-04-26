<<<<<<< HEAD
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

using std::vector;

vector<vector<int>> GenRandomGraphs(unsigned int V, unsigned int E, unsigned int maxCap);

int main( int argc, char* argv[] ) {

    std::ofstream myfile;
    unsigned long numberOfNodes;
    unsigned long maxEdges;
    unsigned long minEdges;
    unsigned long numberOfEdges;
    unsigned long maxCapacity;
    vector<vector<int>> edgeList;
    myfile.open("example.csv");

    if(argc < 4) {
        std::cerr << "ERROR: Insufficient number of arguments" << std::endl;
        std::cerr << "[Format]: ./graph [No. of nodes] [sparse|dense] [Max Capacity]" << std::endl;
        exit(-1);
    }

    if((numberOfNodes = strtoul(argv[1], NULL, 10)) == 0) {
        std::cerr << "ERROR: Could not extract the number of nodes from command line arguments" << std::endl;
        std::cerr << "[Format]: ./graph [No. of nodes] [sparse|dense] [Max Capacity]" << std::endl;
        exit(-1);
    }

    if(strcmp(argv[2], "dense") == 0) {
        maxEdges = numberOfNodes * (numberOfNodes - 1);
        minEdges = maxEdges / 2;
    } else if(strcmp(argv[2], "sparse")) {
        maxEdges = numberOfNodes * (numberOfNodes - 1) / 2;
        minEdges = numberOfNodes - 1;
    } else {
        std::cerr << "ERROR: incorrect option for 2nd command line arguement" << std::endl;
        std::cerr << "[Format]: ./graph [No. of nodes] [sparse|dense] [Max Capacity]" << std::endl;
        exit(-1);
    }

    numberOfEdges = (rand() % (maxEdges - minEdges)) + minEdges;

    if((maxCapacity = strtoul(argv[3], NULL, 10)) == 0) {
        std::cerr << "ERROR: Could not extract max capacity from command line arguments" << std::endl;
        std::cerr << "[Format]: ./graph [No. of nodes] [sparse|dense] [Max Capacity]" << std::endl;
        exit(-1);
    }

    edgeList = GenRandomGraphs(numberOfNodes, numberOfEdges, maxCapacity);

    myfile << "source,destination,capacity\n";
    for(vector<int>& edge : edgeList) {
        myfile << edge[0] << ',' << edge[1] << ',' << edge[2] << '\n';
    }
    myfile.close();
    return 0;

}

// C++ code to implement the approach
  
// Function to generate random graph
vector<vector<int>> GenRandomGraphs(unsigned int V, unsigned int E, unsigned int maxCap)
{
    
    int i, j, count;
    // Edge list
    vector<vector<int>> edges(E, vector<int> (3, 0));
    i = 0;
  
    // Assign random values to the number
    // of vertex and edges of the graph,
    // Using rand().
    while (i < V) {
    initEdge:
        edges[i][0] = rand() % V + 1;
        edges[i][1] = rand() % V + 1;
  
        // Print the connections of each
        // vertex, irrespective of the
        // direction.
        if(edges[i][0] == edges[i][1]) { // self-loop
            goto initEdge;
        } 
        for (j = 0; j < i; j++) {
            if ((edges[i][0] == edges[j][0] && edges[i][1] == edges[j][1]) // edge is a duplicate
                || (edges[i][0] == edges[j][0])) { // 
                    goto initEdge;
                }
        }
        edges[i][3] = (rand() % (maxCap - 1)) + 1;
        i++;
    }

    return edges;
}
=======
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(NULL)); // initialize random seed
    
    int n = 10; // starting number of nodes
    int m = 5; // number of graphs to generate
    
    ofstream fout("graphs.csv"); // open output file
    
    for (int i = 0; i < m; i++) {
        int source = rand() % n;
        int sink = rand() % n;
        while (sink == source) { // make sure sink is not the same as source
            sink = rand() % n;
        }
        
        fout << "Source," << source << endl; // write source vertex
        fout << "Sink," << sink << endl; // write sink vertex
        fout << "Source,Destination,Weight" << endl; // write header
        
        for (int j = 0; j < n; j++) {
            if (j != source && j != sink) { // ignore source and sink nodes
                for (int k = 0; k < n; k++) {
                    if (j != k) { // ignore self-loops
                        int weight = rand() % 100 + 1; // generate random weight between 1 and 100
                        fout << j << "," << k << "," << weight << endl; // write edge to file
                    }
                }
            }
        }
        
        n += 10; // increase number of nodes for next graph
    }
    
    fout.close(); // close output file
    
    cout << "Graphs saved to graphs.csv." << endl;
    
    return 0;
}


>>>>>>> e28ee2d (completed algorithm)
