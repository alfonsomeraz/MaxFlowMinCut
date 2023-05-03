# MaxFlowMinCut
This repository stores the maximum flow minimum cut algorithmic analysis code for EC504: Advanced Data Structures and Algorithms


## Theorem
In computer science and optimization theory, the max-flow min-cut theorem states that in a flow network, the maximum amount of flow passing from the source to the sink is equal to the total weight of the edges in a minimum cut, i.e., the smallest total weight of the edges which if removed would disconnect the source from the sink.


## Project Overview
Team: Alfonso Meraz, Nathaniel Voss, Mark Nudleman, Sasha Dolynuk (U57701712, adolynuk), Justin Sadler

## Abstract
Flow network graphs model the transport of items from a source to a sink using a network of routes where each edge is directed and has a capacity. Maximum flow is an optimization problem that searches for the maximum possible flow rate through a network using multiple paths from source to sink. This problem has many applications including transport systems, the flow of information through computer networks, and image segmentation. The max-flow min-cut theorem states that the maximum possible flow for a network is equal to the minimum capacity over all cuts of the network. By examining the minimum cut of a network, one can analyze how the maximum flow is limited.

This project applies the Edmunds-Karp implementation of the Ford-Fulkerson algorithm to multiple pedestrian transit flow network problems based on the layout of the city of Boston. By developing multiple interpretations of how pedestrians flow through geographical areas, we were able to design multiple graphs based on the same map to analyze limiting factors of max flow. In particular, this project compares undirected vs directed edges, unit capacity vs capacity based on realistic measures, and expanded vs condensed/bundled nodes and examines how all of these factors impact the min cut and max flow of the network.

Additionally, to analyze the asymptotic runtime complexity, multiple flow network graphs of varying node and edge amounts were randomly generated. The runtime for each graph was calculated and plotted to analyze the relationship between nodes, edges, and runtime with the expectation that a time complexity of O(V * E^2) would be revealed.

## Instructions to Run Code

In your terminal, clone the repository, go into the 
directory and run make. 
```
git clone git@github.com:alfonsomeraz/MaxFlowMinCut.git
cd MaxFlowMinCut
make maxflow
./maxflow
```
## Problems

* Computer Networking
* Resource Flow
* Transportation

## Solution

## Results & Analysis
### Sample Results

*Max-Flow/Min-Cut on Boston Pedestrian Transit Networks*

**Boston University Graph**

Scenario: what is the maximum number of students that can walk from Raising Cane’s (on the west end of campus) to Kenmore Square (on the east end of campus) for dessert?

![bu_flow_img](https://user-images.githubusercontent.com/55323113/236075165-a870055d-ebb3-4d30-a4ca-cf29ad1d9f75.JPG)

**Figure 1**. Flow network graph design based on BU campus with capacities of edges assigned by relatively realistic values of street capacities. Source = Raising Cane’s, sink = Kenmore Square. Each node is an intersection and each edge is a street.

From this graph structure, we created 2 different graphs, one with unit capacity and one with capacities assigned based on how many people could use the street. For the graph unit capacity, the max flow was only 2, while the alternative capacity graph had a max flow of 66. The max flow of 66 comes from adding up all the edges of the min-cut (50+8+8 = 60). This decrease in max flow is because while the graph structure is the same, the source only has 2 edges radiating out from it. Thus when we use unit capacity, we limit the max flow to however many edges radiate from the source node, which in this case was 2.

![min_cut_img](https://user-images.githubusercontent.com/55323113/236075206-fa642974-5b66-4d9c-8d0d-eda2873faf3d.JPG)

**Figure 2**. Min cut corresponding to max flow of BU network. Left: realistic relative capacities. Right: unit capacity.

**Boston Common graph**

Scenario: maximum number of pedestrians that can walk from the broken down T at Arlington St. to Park St. to transfer to the red line?

![boston_common_flow_img](https://user-images.githubusercontent.com/55323113/236075235-e0cce6f6-9f92-4d55-a1ef-f2188d242e24.JPG)

**Figure 3**. Nodes and edges for Boston Common graph. Source = Arlington St, sink = Park St T stop. Each node is an intersection and each edge is a walkway.

From the graph structure shown in Figure 3, we created 2 different versions: a directed and undirected graph. Our results show that the directed graph has a max flow of only 6 people, while the undirected graph has a max flow of 22 people. We inferred that this stark contrast between how many people can get through the network is because the undirected graph allows for more options for which people can walk in order to maximize flow. The directed graph makes assumptions on the direction that people should walk which may not be correct and may limit flow by preventing flow in a productive direction. Additionally, in real life, most streets and walkways are 2-way (undirected).

Lastly, we designed a consolidated version of the Boston Common network by bundling nodes together. This is shown below in Figure 4. After running our algorithm on this graph and comparing it to the version with expanded nodes, we found that the max flow for this bundled node version was twice as much as the alternative, at 44 pedestrians as opposed to only 22. This increase in flow can be attributed to the reduction in congestion and bottlenecks from the rotary structures by bundling those nodes together. 

![bundle_nodes_img](https://user-images.githubusercontent.com/55323113/236075252-fc00c4b9-056b-4482-a744-ed6d637a3c95.JPG)

**Figure 4**. Expanded (left) and consolidated (right) version of the Boston Common flow network.

Our code produces an output file containing the number of nods, number of edges, max flow, and runtime for each csv graph file analyzed. This is pictured below in Figure 5.

![boston_results](https://user-images.githubusercontent.com/55323113/236075269-8b1c6941-0828-4498-98bb-0572a0afa892.JPG)

**Figure 5**. Output file with flow and runtime for all scenarios described above.

We can note that, as expected, graphs with less edges and nodes have a shorter runtime. However, we also see that for graphs with the same number of nodes and edges, there can still be significantly different runtimes. This is best exemplified by a comparison between the regular and unit capacity graphs: each unit capacity graph has a runtime <⅔ of its corresponding varying capacity graph. We can attribute this to the reduction in complexity of calculating the residual graph in the Ford-Fulkerson algorithm.

### Discussion & Conclusion

*Max-Flow/Min-Cut on Boston Pedestrian Transit Networks*

We analyzed different factors that impact the max flow of a flow network. We determined that using unit capacity vs realistically relative capacity values limits the max flow to the amount of edges radiating from the source node if that is the min cut of the graph. Additionally, unit capacity graphs have a faster runtime than their counterparts. We also found that directed graphs limit flow by blocking paths in certain directions, thus to ensure maximum flow, an undirected graph is best. Finally, bundling nodes that are spatially close together reduces congestion and bottlenecks, improving the maximum flow.



## References
