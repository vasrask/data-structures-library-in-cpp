#include "Heap.h"
#include <iostream>

// Constructor to initialize an empty heap
Heap::Heap() : data(nullptr), capacity(0), size(0) {}

// Destructor to deallocate memory
Heap::~Heap() {
    delete[] data;
}

// Builds a heap from an array of elements
void Heap::buildHeap(int* elements, int size, bool (*compare)(int, int)) {
    if (data) {
        delete[] data;
    }

    this->size = size;
    this->capacity = size;
    data = new int[capacity];

    for (int i = 0; i < size; ++i) {
        data[i] = elements[i];
    }

    for (int i = size / 2 - 1; i >= 0; --i) {
        reheapDown(i, compare);
    }
}

// Returns the size of the heap
int Heap::getSize() const {
    return size;
}

// Inserts an element into the heap
void Heap::insert(int element, bool (*compare)(int, int)) {
    if (size >= capacity) {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        int* newData = new int[capacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

    data[size++] = element;
    reheapUp(size - 1, compare);
}

// Removes and returns the root element of the heap
int Heap::extract(bool (*compare)(int, int)) {
    if (size == 0) {
        throw std::runtime_error("Heap is empty");
    }

    int root = data[0];
    data[0] = data[--size];
    reheapDown(0, compare);
    return root;
}

// Prints the heap to a file
void Heap::printHeap(std::string heaptype, std::ofstream& output) {
    output << heaptype;
    for (int i = 0; i < size; ++i) {
        output << data[i] << " ";
    }
    output << std::endl;
}

