#include <iostream>
#include <limits.h>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>
#include <cstring>
using namespace std;
 

/* Returns true if there is a path from source 's' to sink
  't' in residual graph. Also fills parent[] to store the
  path */
bool bfs(vector<vector<int> > rGraph, int s, int t, int parent[], int nodes)
{
    // Create a visited array and mark all vertices as not
    // visited
    bool visited[nodes];
    memset(visited, 0, sizeof(visited));
 
    // Create a queue, enqueue source vertex and mark source
    // vertex as visited
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
 
    // Standard BFS Loop
    while (!q.empty()) {
        int u = q.front();
        q.pop();
 
        for (int v = 0; v < nodes; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                // If we find a connection to the sink node,
                // then there is no point in BFS anymore We
                // just have to set its parent and can return
                // true
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
 
    // We didn't reach sink in BFS starting from source, so
    // return false
    return false;
}

// Returns the maximum flow from s to t in the given graph
int fordFulkerson(vector<vector<int> > graph, int s, int t, int nodes)
{
    int u, v;
    
 
    // Create a residual graph and fill the residual graph
    // with given capacities in the original graph as
    // residual capacities in residual graph
    vector<vector<int> > rGraph(nodes, vector<int> (nodes, 0));

    for (u = 0; u < nodes; u++){
        for (v = 0; v < nodes; v++)
        {
            // cout << "graph[u][v]: " << graph[u][v] << endl;
            rGraph[u][v] = graph[u][v];
        }
    }
        

    int parent[nodes]; // This array is filled by BFS and to
                   // store path
 
    int max_flow = 0; // There is no flow initially
 
    // Augment the flow while there is path from source to
    // sink
    while (bfs(rGraph, s, t, parent, nodes)) {
        // Find minimum residual capacity of the edges along
        // the path filled by BFS. Or we can say find the
        // maximum flow through the path found.
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
 
        // update residual capacities of the edges and
        // reverse edges along the path
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
 
        // Add path flow to overall flow
        max_flow += path_flow;
        // cout << "max_flow: " << max_flow << endl;
    }
 
    // Return the overall flow
    return max_flow;
}

double interval(struct timespec start, struct timespec end){
  struct timespec temp;
  temp.tv_sec = end.tv_sec - start.tv_sec;
  temp.tv_nsec = end.tv_nsec - start.tv_nsec;
  if (temp.tv_nsec < 0) {
    temp.tv_sec = temp.tv_sec - 1;
    temp.tv_nsec = temp.tv_nsec + 1000000000;
  }
  return (((double)temp.tv_sec) + ((double)temp.tv_nsec)*1.0e-9);
}

int main()
{
    struct timespec start, end;
    double timeElapsed;

    // ifstream input_file;

    string files[9] = {"BostonCommonDirected.csv",
                        "BostonCommonUndirected.csv",
                        "BostonCommonUndirectedUnitCap.csv",
                        "BostonCommonDirectedUnitCap.csv",
                        "BostonCommonConsolidatedUndirected.csv",
                        "BostonCommonConsolidatedDirected.csv",
                        "flowBU.csv",
                        "flowNetDense.csv",
                        "flowNetMidBlob.csv"};

    FILE* cFile;
    cFile = fopen ("RuntimeData.txt","w+");
    fprintf(cFile,"Ford-Fulkerson Algorithm\n");
    fprintf(cFile,"------------------------\n");
    fprintf(cFile,"     Nodes     |     Edges     |     Flow     |     Time     |     File     \n");

    for (int i = 0; i < 9; i++)
    {
        
        
        ifstream input_file(files[i]);
        string nodes_str, edges_str;
        int max_nodes, max_edges, actual_num_nodes;
        string line;
        getline(input_file, line);
        stringstream ss(line);
        ss >> nodes_str >> actual_num_nodes >> edges_str >> max_edges;
        fprintf(cFile,"%9.4d  %13.3d ", actual_num_nodes, max_edges);
        
        string source, sink;
        int source_int, sink_int;
        getline(input_file, line);
        stringstream ss2(line);
        ss2 >> source >> source_int >> sink >> sink_int;
        max_nodes = sink_int;
        // cout << "source: " << source_int << endl;
        // cout << "sink: " << sink_int << endl;

        source_int -= 1;
        sink_int -= 1;

        vector<vector<int> > network(max_nodes, vector<int> (max_nodes, 0));
        
        while (getline(input_file, line)) {
            int src, dst, capacity;
            stringstream ss(line);

            string cell;
            if (getline(ss, cell, ','))
                src = stoi(cell); // parse first number
            if (getline(ss, cell, ','))
                dst = stoi(cell); // parse second number
            if (getline(ss, cell, ','))
                capacity = stoi(cell); // parse third number
            

            network[src-1][dst-1] = capacity;
        }
        input_file.close();
        clock_gettime(CLOCK_MONOTONIC, &start);
        // cout << "The maximum possible flow is "
        int max_flow = fordFulkerson(network, source_int, sink_int, max_nodes);
        fprintf(cFile, "%15.3d ", max_flow);
            // << endl;
        clock_gettime(CLOCK_MONOTONIC, &end);

        timeElapsed = interval(start, end);

        fprintf(cFile, "%16.3e ms\t%s\n", timeElapsed, files[i].c_str());
        //cout << "          " << timeElapsed << " ms";
        //cout << "          " << files[i] << endl;
        network.clear();
    }

    

    return 0;
}






