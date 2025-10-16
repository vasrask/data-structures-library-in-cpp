#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>

#include <fstream>
class Graph {
private:
    int vertices;
    std::vector<std::list<std::pair<int, int>>> adjList;

    std::vector<int> dijkstraShortestPath(int source);
    void dfs(int v, std::vector<bool>& visited);
    int find(int parent[], int i);
    void unionSet(int parent[], int x, int y);
    int kruskalMST();

public:
    Graph(int V);
    void addEdge(int v, int w, int weight);
    void resize(size_t newSize);
    void buildGraph(int edges[][3], int size);
    std::pair<int, int> getSize() const;
    int computeShortestPath(int source, int destination);
    int computeSpanningTree();
    int findConnectedComponents();
    bool insertEdge(int source, int destination, int weight);
    bool deleteEdge(int source, int destination);
    void printGraph(std::ofstream& output);

};

#endif // GRAPH_H
