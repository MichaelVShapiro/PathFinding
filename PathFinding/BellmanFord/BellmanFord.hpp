//
//  BellmanFord.hpp
//  Graph Stuff
//
//  Created by Michael Shapiro on 9/20/24.
//

#ifndef BellmanFord_hpp
#define BellmanFord_hpp

#include <stdio.h>
#include <vector>
#include <map>

/**
 * All structures located for this
 */
namespace BellmanFordCore {
/**
 * A directed graph for bellman ford algorithm
 */
class Graph {
private:
    /**
     * Number of vertecies in graph
     */
    int num_vertecies;
    /**
     * Edges in graph
     */
    std::vector<std::vector<std::pair<int, int>>> edges;
public:
    /**
     * Initialize graph with num vertecies
     */
    Graph(int v) {this->num_vertecies = v; this->edges.resize(v);}
    /**
     * Default empty constructor
     */
    Graph() {this->num_vertecies = 0;}
    /**
     * Adds a vertex
     */
    void addVertex() {this->num_vertecies += 1; this->edges.push_back(std::vector<std::pair<int, int>>());}
    /**
     * Add edge
     */
    void addEdge(int u, int v, int e);
    /**
     * Gets edges for vertex u
     */
    std::vector<std::pair<int, int>> getEdges(int u);
    /**
     * Gets number of vertecies
     */
    int getNumVertecies() {return this->num_vertecies;}
};
/**
 * Bellman ford algorithm
 */
class BellmanFord {
private:
    /**
     * Core graph
     */
    Graph g;
    /**
     * Tries to improve the current distance
     */
    void improveDistance(int s, std::vector<std::pair<int, int>> edges, std::vector<int> *cost, std::vector<std::vector<int>> *path);
    /**
     * Computes the optimal path
     */
    std::pair<std::vector<int>, int> computeOptimalPath(int s, int u);
public:
    BellmanFord(Graph g) {this->g = g;}
    /**
     * Computes the shortest path from vertex s to vertex u
     */
    std::pair<std::vector<int>, int> findShortestPath(int s, int u);
};
}

#endif /* BellmanFord_hpp */
