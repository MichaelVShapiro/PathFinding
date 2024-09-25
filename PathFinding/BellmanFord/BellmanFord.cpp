//
//  BellmanFord.cpp
//  Graph Stuff
//
//  Created by Michael Shapiro on 9/20/24.
//

#include <queue>
#include <set>
#include "BellmanFord.hpp"

void BellmanFordCore::Graph::addEdge(int u, int v, int e) {
    // make sure u and v exist
    if(u >= this->num_vertecies || v >= this->num_vertecies)
        throw "invalid vertex provided";
    
    this->edges[u].push_back(std::make_pair(v, e));
}

std::vector<std::pair<int, int>> BellmanFordCore::Graph::getEdges(int u) {
    // make sure u exists
    if(u >= this->num_vertecies)
        throw "vertex u (" + std::to_string(u) + ") does not exist in graph G";
    
    return this->edges[u];
}

void BellmanFordCore::BellmanFord::improveDistance(int s, std::vector<std::pair<int, int>> edges, std::vector<int> *cost, std::vector<std::vector<int>> *path) {
    // get cost of s
    int s_cost = (*cost)[s];
    
    // now go through each edge and see if it improves anything
    for(auto i : edges) {
        int new_cost = s_cost + i.second;
        
        // see if new cost is better than old cost for v
        int v = i.first;
        if(new_cost < (*cost)[v]) {
            // better path found!
            // update table
            (*cost)[v] = new_cost;
            
            // also update new path
            (*path)[v] = (*path)[s];
            (*path)[v].push_back(v);
        }
    }
}

std::pair<std::vector<int>, int> BellmanFordCore::BellmanFord::computeOptimalPath(int s, int u) {
    // get maximum number of iterations needed
    // this is equal to number of vertecies - 1
    int num_iterations = this->g.getNumVertecies() - 1;
    
    // set up table
    std::vector<int> optimal_cost;
    std::vector<std::vector<int>> optimal_path;
    optimal_cost.resize(this->g.getNumVertecies());
    optimal_path.resize(this->g.getNumVertecies());
    
    // make optimal path for s start with s
    optimal_path[0].push_back(s);
    
    // set all costs in optimal cost to infinity
    // except for vertex s
    for(int i = 0; i < optimal_cost.size(); i++) {
        if(i != s) {
            optimal_cost[i] = INT_MAX;
        }
    }
    
    // through each iteration, try to improve distances
    int iter = 1;
    while(iter <= num_iterations) {
        // try to improve distances for nodes
        std::queue<int> bfsq;
        bfsq.push(s);
        
        std::set<int> visited;
        
        while(!bfsq.empty()) {
            int uu = bfsq.front();
            bfsq.pop();
            
            // make sure uu is not visitied
            if(visited.contains(uu)) continue;
            
            visited.insert(uu);
            
            // get edges
            std::vector<std::pair<int, int>> e = this->g.getEdges(uu);
            
            // try to improve path
            this->improveDistance(uu, e, &optimal_cost, &optimal_path);
            
            // add adjacent vertecies to queue
            for(auto i : e) {
                bfsq.push(i.first);
            }
        }
        
        // increment iter
        iter += 1;
    }
    
    // the last thing to do is make sure we have no negative cycles
    // we will have a negative cyle if we detect that the path can be improved once again
    // this makes sense because its a sign which shows that per each iteration, that path can constantly be improved
    std::queue<int> bfsq2;
    bfsq2.push(s);
    std::set<int> visitied2;
    
//    while(!bfsq2.empty()) {
//        int uu = bfsq2.front();
//        bfsq2.pop();
//        
//        if(visitied2.contains(uu)) continue;
//        
//        visitied2.insert(uu);
//        
//        // do same thing as before
//        std::vector<std::pair<int, int>> e = this->g.getEdges(uu);
//        
//        // we don't have to improve anything here
//        // just check if the distance gets smaller
//        for(auto i : e) {
//            int v = i.first;
//            int w = i.second;
//            
//            if(optimal_cost[v] + w < optimal_cost[v]) {
//                // cycle found!
//                // cost keeps getting smaller!
//                throw "Negative cycle detected!";
//            }
//            
//            bfsq2.push(i.first);
//        }
//    }
    
    // by this point, there is no more negative cycle
    // make sure u has an optimal cost
    if(optimal_cost[u] == INT_MAX) throw "path to u not found!";
    
    return std::make_pair(optimal_path[u], optimal_cost[u]);
}

std::pair<std::vector<int>, int> BellmanFordCore::BellmanFord::findShortestPath(int s, int u) {
    // make sure s and u are valid
    if(s >= this->g.getNumVertecies() || u >= this->g.getNumVertecies()) throw "invalid vertex given";
    
    // now compute path
    return this->computeOptimalPath(s, u);
}
