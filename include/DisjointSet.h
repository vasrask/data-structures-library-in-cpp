#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <vector>
// This class is used for finding the spanning tree of a graph
class DisjointSet {
private:
    std::vector<int> parent; // Stores the parent of each element

public:
    DisjointSet(int n) : parent(n, -1) {}

    // Finds the representative of the set containing element i
    int find(int i) {
        if (parent[i] == -1)
            return i;
        return find(parent[i]);
    }

    // Unites the sets containing elements x and y
    void unionSet(int x, int y) {
        int xset = find(x);
        int yset = find(y);
        if (xset != yset)
            parent[xset] = yset;
    }
};

#endif // DISJOINTSET_H
