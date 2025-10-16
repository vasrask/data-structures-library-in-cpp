#include "Graph.h"
#include "CustomAlgorithm.h"
#include "CustomQueue.h"
#include "DisjointSet.h"
#include <iostream>

// Constructor to initialize the graph with V vertices
Graph::Graph(int V) : vertices(V), adjList(V) {}

// Adds an edge to the graph during the building process
void Graph::addEdge(int v, int w, int weight) {
    adjList[v].emplace_back(w, weight);
    adjList[w].emplace_back(v, weight);
}

/*void printVectorOfLists(const std::vector<std::list<std::pair<int, int>>>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << "Index " << i << ":";
        for (const auto& p : vec[i]) {
            std::cout << " (" << p.first << ", " << p.second << ")";
        }
        std::cout << std::endl;
    }
}*/

// Builds the graph from an array of edges
void Graph::buildGraph(int edges[][3], int size) {
    for (int i = 0; i < size; ++i) {
        addEdge(edges[i][0], edges[i][1], edges[i][2]);
    }
    //printVectorOfLists(adjList);
}

// Returns the size of the graph
std::pair<int, int> Graph::getSize() const {
    int numVertices = vertices;
    int numEdges = 0;
    for (int v = 0; v < vertices; ++v) {
        numEdges += adjList[v].size();
    }
    return {numVertices, numEdges / 2};
}

// Dijkstra's algorithm
std::vector<int> Graph::dijkstraShortestPath(int source) {
    std::vector<int> dist(vertices, INT_MAX);
    CustomQueue<std::pair<int, int>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.isEmpty()) {
        int u = pq.front().second;
        pq.pop();

        for (const auto& neighbor : adjList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

// Computes the shortest path from source to destination using Dijkstra's algorithm
int Graph::computeShortestPath(int source, int destination){
    std::vector<int> dist = dijkstraShortestPath(source);
    return dist[destination];
}

// Compares edges by weight
bool compareEdges(const std::pair<int, std::pair<int, int>>& edge1, const std::pair<int, std::pair<int, int>>& edge2) {
    return edge1.first > edge2.first;
}

// Kruskal's algorithm
int Graph::kruskalMST() {
    std::vector<std::pair<int, std::pair<int, int>>> edges;
    for (int v = 0; v < vertices; ++v) {
        for (const auto& neighbor : adjList[v]) {
            int u = neighbor.first;
            int weight = neighbor.second;
            edges.push_back({weight, {v, u}});
        }
    }

    CustomAlgorithm<std::pair<int, std::pair<int, int>>>::sort(edges, compareEdges);
   /* std::cout << "Sorted Edges:" << std::endl;
    for (const auto& edge : edges) {
        int u = edge.second.first;
        int v = edge.second.second;
        int weight = edge.first;
        std::cout << u << " - " << v << " : " << weight << std::endl;
    }*/
    std::vector<std::pair<int, std::pair<int, int>>> spanningTreeEdges;

    int minCost = 0;
    DisjointSet disjointSet(vertices);
    for (const auto& edge : edges) {
        int u = edge.second.first;
        int v = edge.second.second;
        int setU = disjointSet.find(u);
        int setV = disjointSet.find(v);
        if (setU != setV) {
            minCost += edge.first;
            disjointSet.unionSet( setU, setV);
            spanningTreeEdges.push_back({edge.first, {u,v}});

        }
    }

  /*  std::cout << "Spanning Tree Edges:\n";
    for (const auto& edge : spanningTreeEdges) {
        std::cout << edge.second.first << " - " << edge.second.second << " : " << edge.first << std::endl;
    }*/
    return minCost;
}

// Computes the minimum spanning tree using Kruskal's algorithm
int Graph::computeSpanningTree(){
    return kruskalMST();
}

// DFS algorithm
void Graph::dfs(int v, std::vector<bool>& visited) {
    visited[v] = true;
    for (const auto& neighbor : adjList[v]) {
        int u = neighbor.first;
        if (!visited[u]) {
            dfs(u, visited);
        }
    }
}

// Finds the connected components of the graph
int Graph::findConnectedComponents(){
     int components = 0;
    std::vector<bool> visited(vertices, false);
    for (int v = 0; v < vertices; ++v) {
        if (!visited[v]) {
            dfs(v, visited);
            components++;
        }
    }
    return components;
}

// Resizes the graph to newSize vertices
void Graph::resize(size_t newSize) {
    if (newSize <= vertices) {
        for (int i = newSize; i < vertices; ++i) {
            adjList[i].clear();
        }
    adjList.resize(newSize);
   vertices = newSize;
    }
}

// Inserts an edge into the graph
bool Graph::insertEdge(int source, int destination, int weight) {
    if (source < 0 || source >= vertices || destination < 0 || destination >= vertices)
        return false;

    for (const auto& edge : adjList[source]) {
        if (edge.first == destination)
            return false;
    }

    adjList[source].emplace_back(destination, weight);
    adjList[destination].emplace_back(source, weight);
    return true;
}

// Deletes an edge from the graph
bool Graph::deleteEdge(int source, int destination) {
    if (source < 0 || source >= vertices || destination < 0 || destination >= vertices)
        return false;

    for (auto it = adjList[source].begin(); it != adjList[source].end(); ++it) {
        if (it->first == destination) {
            adjList[source].erase(it);
            break;
        }
    }

    for (auto it = adjList[destination].begin(); it != adjList[destination].end(); ++it) {
        if (it->first == source) {
            adjList[destination].erase(it);
            break;
        }
    }

    return true;
}

// Prints the graph to a file
void Graph::printGraph(std::ofstream& output) {
    for (int v = 0; v < vertices; ++v) {
        output << "Vertex " << v << ":\n";
        for (const auto& neighbor : adjList[v]) {
            output << " -> " << neighbor.first << " (weight " << neighbor.second << ")\n";
        }
    }
}
