#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "Heap.h"

class MaxHeap : public Heap {
protected:
    void reheapDown(int index, bool (*compare)(int, int)) override;
    void reheapUp(int index, bool (*compare)(int, int)) override;

public:
    static bool compare(int a, int b) {
        return a > b;
    }
    int findMax() const;
};

#endif // MAXHEAP_H
