# MaxFlowMinCut
This repository stores the maximum flow minimum cut algorithmic analysis code for EC504: Advanced Data Structures and Algorithms


### Theorem
In computer science and optimization theory, the max-flow min-cut theorem states that in a flow network, the maximum amount of flow passing from the source to the sink is equal to the total weight of the edges in a minimum cut, i.e., the smallest total weight of the edges which if removed would disconnect the source from the sink.


## Project Overview
Team: Alfonso Meraz, Nathaniel Voss, Mark Nudleman, Sasha Dolynuk (U57701712, adolynuk), Justin Sadler

### Abstract
Flow network graphs model the transport of items from a source to a sink using a network of routes where each edge is directed and has a capacity. Maximum flow is an optimization problem that searches for the maximum possible flow rate through a network using multiple paths from source to sink. This problem has many applications including transport systems, the flow of information through computer networks, and image segmentation. The max-flow min-cut theorem states that the maximum possible flow for a network is equal to the minimum capacity over all cuts of the network. By examining the minimum cut of a network, one can analyze how the maximum flow is limited.

This project applies the Edmunds-Karp implementation of the Ford-Fulkerson algorithm to multiple pedestrian transit flow network problems based on the layout of the city of Boston. By developing multiple interpretations of how pedestrians flow through geographical areas, we were able to design multiple graphs based on the same map to analyze limiting factors of max flow. In particular, this project compares undirected vs directed edges, unit capacity vs capacity based on realistic measures, and expanded vs condensed/bundled nodes and examines how all of these factors impact the min cut and max flow of the network.

Additionally, to analyze the asymptotic runtime complexity, multiple flow network graphs of varying node and edge amounts were randomly generated. The runtime for each graph was calculated and plotted to analyze the relationship between nodes, edges, and runtime with the expectation that a time complexity of O(V * E^2) would be revealed.

### Instructions to Run Code

In your terminal, clone the repository, go into the 
directory and run make. 
```
git clone git@github.com:alfonsomeraz/MaxFlowMinCut.git
cd MaxFlowMinCut
make maxflow
./maxflow
```
### Problems

* Computer Networking
* Resource Flow
* Transportation

### Solution

### Results

### Analysis

### References
