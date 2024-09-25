#  Shortest Path Algorithms

In this repository are a few algorithms I implemented a while ago. In particular, [Dijkstra](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm) and [Bellman-Ford](https://en.wikipedia.org/wiki/Bellman–Ford_algorithm). Both of these algorithms can find the shortest path from one vertex to another in a directed weighted graph.

## The Difference between Dijkstra and Bellman-Ford

Dijkstra algorithm doesn't work with negative weights while Bellman-Ford does, provided that the graph doesn't have a negative cycle. A negative cycle is simply a cycle in the graph that has edges with negative weights which makes it harder to find a path that improves the distance (from the start vertex). The thing about this cycle is that because of the negative weights, it is possible to constantly improve the shortest path to the target vertex. And this causes the cycle during the algorithm, therefore, making it harder to determine the optimal path.

The two algorithms also have different time complexities. Dijkstra's algorithm has the expected runtime of O(E) where _E_ is the number of edges. Bellman-Ford has the expected runtime of O(V \* E) where _V_ is the number of vertecies and _E_ is the number of edges.

## Use by Terminal

See "test.txt" for an example of using this by terminal. The first line in "test.txt" describes the number of vertecies in the graph. The line below it is the "start" vertex. The next line is the vertex to find the shortest distance from the "start" vertex.

From there, you can assign your edge weights using the syntax: _v u w_ where v and u are the vertecies, and w is the edge weight respectively. Note that both vertecies are 0-based indexing. Finally, the syntax for executing by terminal:

```console
./main (--dijkstras|--bellmanford) "path/to/graph.txt"
```

## Use by API

The rest of this section will describe how to use the API I made.

```cpp
#include <iostream>
#include <vector>
#include "Dijkstras/dijkstra.hpp"

// this example features how to use get the shortest path using dijkstras algorithm

int main() {
    std::vector<std::vector<int>> graph;
    graph.resize(30); // for 30 vertecies, standard adjacency matrix
    graph[0][1] = 1; // any edge weights you assign to 0 simply means there is no edge between the two vertecies
    //... assuming all weights are set up
    Dijkstra path_finding;
    std::vector<int> shortest_path = path_finding.findShortestPath(graph, 0, 3); // we input the graph, note the start vertex is "0" and we are finding the fastest path to vertex "3"
    // the algorithm returns the full path of the shortest distance
    for(int i = 0; i < shortest_path.size(); i++) {
        if(i == shortest_path.size() - 1) {
            std::cout << shortest_path[i] << std::endl;
            break;
        }
        std::cout << shortest_path[i] << " -> ";
    }
    
    int optimal_cost = path_finding.getDistance();
    
    std::cout << "Shortest Distance: " << optimal_cost << std::endl;
}
```

This next example shows Bellman-Ford.

```cpp
#include <iostream>
#include <vector>
#include "BellmanFord/BellmanFord.hpp"

int main() {
    // since this algorithm allows negative weights, we need to use the graph class built in
    BellmanFordCore::Graph g(20); // we initialize with 20 vertecies
    g.addEdge(0, 1, -1);
    //... assuming all weights are set up
    
    BellmanFordCore::BellmanFord bf(g); // we pass in our graph into the constructor
    std::pair<std::vector<int>, int> shortest_path = bf.findShortestPath(0, 3);
    
    std::vector<int> path = shortest_path.first;
    for(int i = 0; i < path.size(); i++) {
        if(i == path.size() - 1) {
            std::cout << path[i] << std::endl;
            break;
        }
        
        std::cout << path[i] << " -> ";
    }
    
    int optimal_cost = shortest_path.second;
    
    std::cout << "Shortest Distance: " << optimal_cost << std::endl;
}
```
