//
//  dijkstra.hpp
//  Graph Stuff
//
//  Created by Michael Shapiro on 8/15/24.
//

#ifndef dijkstra_hpp
#define dijkstra_hpp

#include <vector>
#include <map>
#include <set>
#include <math.h>
#include <stdio.h>

/**
 * Main class for dijsktra
 */
class Dijkstra {
private:
    /**
     * Core graph
     */
    std::vector<std::vector<int>> graph_core;
    /**
     * Distance from two vertecies
     */
    int distance = -1;
    /**
     * Core algorithm for dijsktra
     */
    std::vector<int> findShortestPath(int v, int w, std::set<int> unvisited_vertecies, std::map<int, int> vertex_weight);
public:
    /**
     * Finds the shortest path from vertex v to vertex w
     */
    std::vector<int> findShortestPath(std::vector<std::vector<int>> g, int v, int w);
    /**
     * Gets the distance between the two vertecies
     */
    int getDistance();
};

#endif /* dijkstra_hpp */
