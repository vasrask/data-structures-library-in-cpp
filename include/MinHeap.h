#ifndef MINHEAP_H
#define MINHEAP_H

#include "Heap.h"

class MinHeap : public Heap {
protected:
    void reheapDown(int index, bool (*compare)(int, int)) override;
    void reheapUp(int index, bool (*compare)(int, int)) override;

public:
    static bool compare(int a, int b) {
        return a < b;
    }
    int findMin() const;
};

#endif // MINHEAP_H
