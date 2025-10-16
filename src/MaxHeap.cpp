#include "MaxHeap.h"

// Performs a downward heapification starting from the given index
void MaxHeap::reheapDown(int index, bool (*compare)(int, int)) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;

    if (left < size && compare(data[left], data[largest])) {
        largest = left;
    }

    if (right < size && compare(data[right], data[largest])) {
        largest = right;
    }

    if (largest != index) {
        CustomAlgorithm<int>::swap(data[index], data[largest]);
        reheapDown(largest, compare);
    }
}

// Performs an upward heapification starting from the given index
void MaxHeap::reheapUp(int index, bool (*compare)(int, int)) {
    int parent = (index - 1) / 2;

    if (index && compare(data[index], data[parent])) {
        CustomAlgorithm<int>::swap(data[index], data[parent]);
        reheapUp(parent, compare);
    }
}

// Finds and returns the maximum element in the heap
int MaxHeap::findMax() const { return size > 0 ? data[0] : -1; }
