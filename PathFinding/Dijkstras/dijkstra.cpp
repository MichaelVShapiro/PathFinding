//
//  dijkstra.cpp
//  Graph Stuff
//
//  Created by Michael Shapiro on 8/15/24.
//

#include <queue>
#include <assert.h>
#include "dijkstra.hpp"

std::vector<int> Dijkstra::findShortestPath(int v, int w, std::set<int> unvisited_vertecies, std::map<int, int> vertex_weight) {
    std::vector<int> path;
    std::map<int, std::pair<int, int>> parent;
    // init bfs queue
    std::queue<int> bfs;
    // enqueue start vertex
    bfs.push(v);
    
    std::set<int> v_set;
    v_set.insert(v); // the source is where we start!
    
    // go through each vertex in the bfs queue
    while(!bfs.empty()) {
        // dequeue item
        int vertex = bfs.front();
        bfs.pop();
        
        // mark edge as visited if not already marked
        if(unvisited_vertecies.contains(vertex)) {
            unvisited_vertecies.erase(vertex);
        }
        
        // get edges
        std::vector<int> edges = this->graph_core[vertex];
        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq;
        
        // go through edges
        for(int i = 0; i < edges.size(); i++) {
            // skip any which don't exist
            if(edges[i] == 0) {
                continue;
            }
            
            // also skip any which have already been visited
            if(!unvisited_vertecies.contains(i)) {
                continue;
            }
            
            // make sure edge weight is positive
            // dijkstras algorithm doesn't work with negative edges
            assert(edges[i] > 0);
            
            // insert into heap
            pq.push(std::make_pair(edges[i], i));
        }
        
        // go through heap
        // update the vertecies as visited
        // input their weights into the map
        // and add them to the bfs queue
        while(!pq.empty()) {
            // remove front
            std::pair<int, int> ee = pq.top();
            pq.pop();
            
            int e = ee.first;
            
            int edge_weight = vertex_weight[vertex] + e;
            
            // check if the vertex weight has already been set
            if(v_set.contains(ee.second)) {
                // compare new edge weight to old
                // and reset if the weight is smaller
                if(vertex_weight[ee.second] < edge_weight) {
                    // no reason to make any changes!
                    // so skip it
                    continue;
                }
            }
            
            // add to bfs
            bfs.push(ee.second);
            
            // update weights
            // new weight = weight of previous node + edge weight
            vertex_weight[ee.second] = edge_weight;
            
            // mark node as weight added
            v_set.insert(ee.second);
            
            // also add parent info
            parent[ee.second] = std::make_pair(vertex, e);
        }
    }
    
    // update distance
    this->distance = vertex_weight[w]; // w should have been touched on
    
    // now input full path to vertex
    // we can simply apply a revered-bfs using the parent map made
    
    int parent_get = w;
    do {
        path.push_back(parent_get);
        parent_get = parent[parent_get].first;
    } while (parent_get != v);
    
    // add final start vertex
    path.push_back(v);
    
    // our current path is reversed
    // so reverse it to make it look more proper
    
    std::reverse(path.begin(), path.end());
    
    return path;
}

std::vector<int> Dijkstra::findShortestPath(std::vector<std::vector<int>> g, int v, int w) {
    // set graph core
    this->graph_core = g;
    // make all vertecies unvisited
    // and set all to infinity, except for start vertex
    std::set<int> uv;
    std::map<int, int> vw;
    for(int i = 0; i < g.size(); i++) {
        // make sure row is of proper size
        assert(g[i].size() == g.size());
        uv.insert(i);
        vw[i] = INFINITY;
    }
    vw[v] = 0;
    return this->findShortestPath(v, w, uv, vw);
}

int Dijkstra::getDistance() {
    // make sure it is set
    assert(this->distance != -1);
    
    return this->distance;
}
