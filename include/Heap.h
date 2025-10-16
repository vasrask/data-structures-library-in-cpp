#ifndef HEAP_H
#define HEAP_H
#include <fstream>
#include <string>
#include "CustomAlgorithm.h"

class Heap {
protected:
    int* data;
    int capacity;
    int size;
    virtual void reheapDown(int index, bool (*compare)(int, int)) = 0;
    virtual void reheapUp(int index, bool (*compare)(int, int)) = 0;

public:
    Heap();
    virtual ~Heap();
    void buildHeap(int* elements, int size, bool (*compare)(int, int));
    int getSize() const;
    virtual void insert(int element, bool (*compare)(int, int));
    virtual int extract(bool (*compare)(int, int));
    void printHeap(std::string heaptype, std::ofstream& output);
};

#endif // HEAP_H
