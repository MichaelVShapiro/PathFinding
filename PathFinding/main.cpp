//
//  main.cpp
//  PathFinding
//
//  Created by Michael Shapiro on 9/24/24.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Dijkstras/dijkstra.hpp"
#include "BellmanFord/BellmanFord.hpp"

/**
 * Standard help
 */
void help() {
    std::cout << "Usage: " << std::endl;
    std::cout << "./main (--dijkstras|--bellmanford) \"path/to/file.txt\"" << std::endl;
}

int main(int argc, const char * argv[]) {
    // we will accept a file from argv
    if(argc == 1) {
        help();
        return 0;
    } else if(argc == 2) {
        std::string c = argv[1];
        if(c != "--help") {
            std::cerr << "Unknown command, run --help" << std::endl;
            return -1;
        }
        
        help();
        return 0;
    }
    
    // by this point only length of 3 is allowed
    if(argc != 3) {
        std::cerr << "Invalid command passed in. Run --help for usage info" << std::endl;
        return -1;
    }
    
    std::string c = argv[1];
    if(c != "--dijkstras" && c != "--bellmanford") {
        std::cerr << "Unknown algorithm given" << std::endl;
        return -1;
    }
    
    std::string pathtxt = argv[2];
    std::ifstream g_get(pathtxt);
    
    if(c == "--dijkstras") {
        std::vector<std::vector<int>> g;
        std::string file_txt;
        int l = 1;
        int start = -1;
        int end = -1;
        while(std::getline(g_get, file_txt)) {
            if(l == 1) {
                // num vertecies
                int numv = std::stoi(file_txt);
                g.resize(numv);
                // also resize inner
                for(int i = 0; i < g.size(); i++) {
                    g[i].resize(numv);
                }
                l += 1;
                continue;
            } else if(l == 2) {
                // start vertex
                start = std::stoi(file_txt);
                l += 1;
                continue;
            } else if(l == 3) {
                end = std::stoi(file_txt);
                l += 1;
                continue;
            }
            
            // edges
            // edge line: u v w (where u and v are vertecies and w is weight)
            
            std::stringstream ss(file_txt);
            std::string w;
            int temp = 1;
            int v = -1;
            int u = -1;
            int ww = -1;
            while(ss >> w) {
                if(temp == 1) {
                    v = std::stoi(w);
                    temp += 1;
                    continue;
                } else if(temp == 2) {
                    u = std::stoi(w);
                    temp += 1;
                    continue;
                }
                
                // temp = 3
                ww = std::stoi(w);
                break;
            }
            
            if(ww < 0) {
                // negative edge weights not aloud!
                std::cerr << "negative edge weight detected! This is not allowed in Dijkstras algorithm" << std::endl;
                return -1;
            }
            
            g[v][u] = ww;
        }
        
        // do core algorithm
        Dijkstra d;
        std::vector<int> path = d.findShortestPath(g, start, end);
        
        std::cout << "shortest path: ";
        for(int i = 0; i < path.size(); i++) {
            if(i == path.size() - 1) {
                std::cout << path[i] << std::endl;
                break;
            }
            std::cout << path[i] << " -> ";
        }
        
        std::cout << "total cost: " << d.getDistance() << std::endl;
        return 0;
    }
    
    // bellman-ford
    BellmanFordCore::Graph g;
    std::string file_txt;
    int l = 1;
    int start = -1;
    int end = -1;
    while(std::getline(g_get, file_txt)) {
        if(l == 1) {
            // num vertecies
            int numv = std::stoi(file_txt);
            g = BellmanFordCore::Graph(numv);
            l += 1;
            continue;
        } else if(l == 2) {
            // start vertex
            start = std::stoi(file_txt);
            l += 1;
            continue;
        } else if(l == 3) {
            end = std::stoi(file_txt);
            l += 1;
            continue;
        }
        
        // edges
        // edge line: u v w (where u and v are vertecies and w is weight)
        
        std::stringstream ss(file_txt);
        std::string w;
        int temp = 1;
        int v = -1;
        int u = -1;
        int ww = -1;
        while(ss >> w) {
            if(temp == 1) {
                v = std::stoi(w);
                temp += 1;
                continue;
            } else if(temp == 2) {
                u = std::stoi(w);
                temp += 1;
                continue;
            }
            
            // temp = 3
            ww = std::stoi(w);
            break;
        }
        
        g.addEdge(v, u, ww);
    }
    
    BellmanFordCore::BellmanFord bf(g);
    std::pair<std::vector<int>, int> res = bf.findShortestPath(start, end);
    
    std::cout << "shortest path: ";
    
    for(int i = 0; i < res.first.size(); i++) {
        if(i == res.first.size() - 1) {
            std::cout << res.first[i] << std::endl;
            break;
        }
        std::cout << res.first[i] << " -> ";
    }
    
    std::cout << "total cost: " << res.second << std::endl;
    
    g_get.close();
    
    return 0;
}
