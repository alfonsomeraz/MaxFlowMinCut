#include <iostream>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

const int MAXN = 1000;

int n, m; // number of vertices and edges
int c[MAXN][MAXN]; // capacity matrix
int f[MAXN][MAXN]; // flow matrix
int s, t; // source and sink vertices
int parent[MAXN]; // parent of each vertex in the augmenting path

int bfs() {
    queue<int> q;
    q.push(s);
    memset(parent, -1, sizeof(parent)); // reset parent array
    parent[s] = -2;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++) {
            if (parent[v] == -1 && c[u][v] - f[u][v] > 0) {
                parent[v] = u;
                if (v == t) return true; // found augmenting path
                q.push(v);
            }
        }
    }
    return false; // no augmenting path found
}

int fordFulkerson() {
    int maxFlow = 0;
    while (bfs()) { // while there is an augmenting path
        int flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            flow = min(flow, c[u][v] - f[u][v]);
        }
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            f[u][v] += flow;
            f[v][u] -= flow;
        }
        maxFlow += flow;
    }
    return maxFlow;
}

int main() {
    n = 4; // number of vertices
    m = 5; // number of edges
    s = 0; // source vertex
    t = 3; // sink vertex
    c[0][1] = 2; // capacity of edge (0, 1)
    c[0][2] = 3; // capacity of edge (0, 2)
    c[1][2] = 1; // capacity of edge (1, 2)
    c[1][3] = 2; // capacity of edge (1, 3)
    c[2][3] = 3; // capacity of edge (2, 3)
    cout << "Maximum flow: " << fordFulkerson() << endl;
    return 0;
}

