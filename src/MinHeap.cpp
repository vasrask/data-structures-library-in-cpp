#include "MinHeap.h"

// Performs a downward heapification starting from the given index
void MinHeap::reheapDown(int index, bool (*compare)(int, int)) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < size && compare(data[left], data[smallest])) {
        smallest = left;
    }

    if (right < size && compare(data[right], data[smallest])) {
        smallest = right;
    }

    if (smallest != index) {
        CustomAlgorithm<int>::swap(data[index], data[smallest]);
        reheapDown(smallest, compare);
    }
}

// Performs an upward heapification starting from the given index
void MinHeap::reheapUp(int index, bool (*compare)(int, int)) {
    int parent = (index - 1) / 2;

    if (index && compare(data[index], data[parent])) {
        CustomAlgorithm<int>::swap(data[index], data[parent]);
        reheapUp(parent, compare);
    }
}

// Finds and returns the minimum element in the heap
int MinHeap::findMin() const { return size > 0 ? data[0] : -1; }
