#include "HashTable.h"
#include <iostream>

#include <fstream>

// Constructor to initialize the hash table with a given size
HashTable::HashTable(int size) : capacity(size), table(size) {}

// Hash function to map keys to table indices
int HashTable::hashFunction(int key) {
    return key % capacity;
}

// Inserts a key into the hash table
void HashTable::insert(int key) {
    int index = hashFunction(key);
    table[index].push_back(key);
}

// Builds the hash table from an array of elements
void HashTable::buildTable(int* elements, int size) {
    for (int i = 0; i < size; ++i) {
        insert(elements[i]);
    }
}

// Returns the size of the hash table
int HashTable::getSize() const {
    int size = 0;
    for (int i = 0; i < capacity; ++i) {
        size += table[i].size();
    }
    return size;
}

// Searches for a key in the hash table
std::string HashTable::search(int key) {
    int index = hashFunction(key);
    for (const auto& element : table[index]) {
        if (element == key) {
            return "SUCCESS";
        }
    }
    return "FAILURE";
}

// Prints the hash table to a file
void HashTable::printTable(std::ofstream& output) {
    for (int i = 0; i < capacity; ++i) {
        if (!table[i].empty()) {
            output << "Index " << i << ":";
            for (const auto& element : table[i]) {
                output << " " << element;
            }
            output << std::endl;
        }
    }
}

