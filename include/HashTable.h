#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <list>
#include <vector>
#include <iostream>

class HashTable {
private:
    int capacity;
    std::vector<std::list<int>> table;

    int hashFunction(int key);

public:
    HashTable(int size);
    void insert(int key);
    void buildTable(int* elements, int size);
    void printTable(std::ofstream& output);
    int getSize() const;
    std::string search(int key);
};

#endif // HASHTABLE_H
