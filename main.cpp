/*
This program implements a library for executing various operations on different data structures:
- MinHeap
- MaxHeap
- AVL Tree
- Graph
- Hash Table

The main function initializes instances of these data structures and reads commands from a file "commands.txt".
Each command specifies an action to perform on a specific data structure, along with optional parameters.

Functions:
- `readFile`: Reads integers from a file and stores them in an array.
- `executeCommand`: Executes a command on the specified data structures and writes the output to a file.
- `main`: Initializes data structures, reads commands from a file, executes commands, and writes the output to another file.

Data Structures:
- `MinHeap`: Implements a minimum heap.
- `MaxHeap`: Implements a maximum heap.
- `AVLTree`: Implements an AVL tree.
- `Graph`: Implements a graph.
- `HashTable`: Implements a hash table.

Command Syntax:
Each command consists of an action followed by parameters.
Actions:
- BUILD: Builds a data structure from a file.
- GETSIZE: Retrieves the size of a data structure.
- FINDMIN: Finds the minimum element in a data structure.
- FINDMAX: Finds the maximum element in a data structure.
- SEARCH: Searches for an element in a data structure.
- DELETE: Deletes an element from a data structure.
- DELETEMIN: Deletes the minimum element from a min heap.
- DELETEMAX: Deletes the maximum element from a max heap.
- INSERT: Inserts an element into a data structure.
- COMPUTESHORTESTPATH: Computes the shortest path in a graph using Dijkstra's algorithm.
- COMPUTESPANNINGTREE: Computes the minimum spanning tree of a graph Kruskal's algorithm.
- FINDCONNECTEDCOMPONENTS: Finds the number of connected components in a graph using the DFS algorithm.

Parameters:
- MINHEAP, MAXHEAP, AVLTREE, HASHTABLE, GRAPH: Specifies the data structure.
- Filename: Specifies the file from which to read data for building a data structure.
- Number(s): Additional parameters required by certain actions, such as element value(s) or vertex indices.

Output:
- The program writes the output of each command along with its execution time to a file "output.txt".
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <chrono>
#include <iomanip>
#include "MinHeap.h"
#include "MaxHeap.h"
#include "AVLTree.h"
#include "Graph.h"
#include "HashTable.h"

// Function to read integers from a file
void readFile(const std::string& filename, int& size, int* elements, std::ofstream& output) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        output << "Error: Could not open file " << filename << std::endl;
        return;
    }
    int element;
    while (inputFile >> element) {
        elements[size++] = element;
    }
}

// Function to execute a command from commands.txt
void executeCommand(const std::string& command, MinHeap& minHeap, MaxHeap& maxHeap, AVLTree& avlTree, Graph& graph, HashTable& hashTable, std::ofstream& output) {

    std::istringstream isstr(command);
    std::string action, structureType, filename;
    isstr >> action;

    // Parsing actions and performing corresponding operations - an exhaustive list
    if (action == "BUILD") {
        int size = 0;
        int* elements = new int[1000];
        isstr >> structureType >> filename;
        // Building the specified data structure from a file
        if (structureType == "MINHEAP") {
            readFile(filename, size, elements, output);
            minHeap.buildHeap(elements, size, MinHeap::compare);
            output << "Built MinHeap" << std::endl;
            //minHeap.printHeap("MinHeap: ", output);
        } else if (structureType == "MAXHEAP") {
            readFile(filename, size, elements, output);
            maxHeap.buildHeap(elements, size, MaxHeap::compare);
            output << "Built MaxHeap" << std::endl;
            //maxHeap.printHeap("MaxHeap: ", output);
        } else if (structureType == "AVLTREE") {
            readFile(filename, size, elements, output);
            avlTree.buildTree(elements, size);
            output << "Built AVL Tree" << std::endl;
            //avlTree.printAVLTree(output);
        } else if (structureType == "HASHTABLE") {
            readFile(filename, size, elements, output);
            hashTable.buildTable(elements, size);
            output << "Built Hash Table" << std::endl;
            //hashTable.printTable(output);
        } else if (structureType == "GRAPH") {
            std::ifstream inputFile(filename);
            int edges[1000][3];
            int edgeCount = 0;
            int element;
            std::set<int> vertices;
            while (inputFile >> element) {
                edges[edgeCount][0] = element;
                inputFile >> edges[edgeCount][1] >> edges[edgeCount][2];
                vertices.insert(edges[edgeCount][1]);
                vertices.insert(edges[edgeCount][2]);
                edgeCount++;
            }
            graph.resize(vertices.size());
            graph.buildGraph(edges, edgeCount);
            output << "Built Graph" << std::endl;
            //graph.printGraph(output);
        }

        delete[] elements;
    } else if (action == "GETSIZE") {
        isstr >> structureType;
        if (structureType == "MINHEAP") {
            output << "Size of MinHeap: " << minHeap.getSize() << std::endl;
        } else if (structureType == "MAXHEAP") {
            output << "Size of MaxHeap: " << maxHeap.getSize() << std::endl;
        } else if (structureType == "AVLTREE") {
            output << "Size of AVL Tree: " << avlTree.getSize() << std::endl;
        } else if (structureType == "HASHTABLE") {
            output << "Size of Hash Table: " << hashTable.getSize() << std::endl;
        } else if (structureType == "GRAPH") {
            output << "Vertices of Graph: " << graph.getSize().first <<  ", Edges of Graph: " << graph.getSize().second <<std::endl;
        }
    } else if (action == "FINDMIN") {
        isstr >> structureType;
        if (structureType == "MINHEAP") {
            output << "Minimum element in Min Heap: " << minHeap.findMin() << std::endl;
        } else if (structureType == "AVLTREE") {
            output << "Minimum element in AVL Tree: " << avlTree.findMin() << std::endl;
        }
    } else if (action == "FINDMAX") {
        isstr >> structureType;
        if (structureType == "MAXHEAP") {
            output << "Maximum element in Max Heap: " << maxHeap.findMax() << std::endl;
        }
    } else if (action == "SEARCH") {
        int number;
        isstr >> structureType >> number;
        if (structureType == "AVLTREE") {
            if (avlTree.search(number) == "SUCCESS") {
                output << "SUCCESS: Element " << number << " found in AVL Tree" << std::endl;
            } else {
                output << "FAILURE: Element " << number << " not found in AVL Tree" << std::endl;
            }
        } else if (structureType == "HASHTABLE") {
            if (hashTable.search(number) == "SUCCESS") {
                output << "SUCCESS: Element " << number << " found in Hash Table" << std::endl;
            } else {
                output << "FAILURE: Element " << number << " not found in Hash Table" << std::endl;
            }
        }
    } else if (action == "DELETE") {
        int number;
        isstr >> structureType >> number;
        if (structureType == "AVLTREE") {
            avlTree.deleteNode(number);
            output << "Deleted element " << number << " from AVL Tree" << std::endl;
            //avlTree.printAVLTree(output);
        } else if (structureType == "GRAPH") {
            int number2;
            isstr >> number2;
            graph.deleteEdge(number, number2);
            output << "Deleted edge (" << number << ", " << number2 << ") from Graph" << std::endl;
            //graph.printGraph(output);
        }
    } else if (action == "DELETEMIN") {
        isstr >> structureType;
        if (structureType == "MINHEAP") {
            output << "Deleted minimum element " << minHeap.extract(minHeap.compare) << " from MinHeap" << std::endl;
            //minHeap.printHeap("MinHeap: ", output);
        }
    } else if (action == "DELETEMAX") {
        isstr >> structureType;
        if (structureType == "MAXHEAP") {
            output << "Deleted maximum element " << maxHeap.extract(maxHeap.compare) << " from MaxHeap" << std::endl;
            //maxHeap.printHeap("MaxHeap: ", output);
        }
    } else if (action == "INSERT") {
        int number, number2;
        isstr >> structureType >> number;
        if (structureType == "MINHEAP") {
            minHeap.insert(number, minHeap.compare);
            output << "Inserted " << number << " to MinHeap" << std::endl;
            //minHeap.printHeap("MinHeap: ", output);
        } else if (structureType == "MAXHEAP") {
            maxHeap.insert(number, maxHeap.compare);
            output << "Inserted " << number << " to MaxHeap" << std::endl;
            //maxHeap.printHeap("MaxHeap: ", output);
        } else if (structureType == "AVLTREE") {
            avlTree.insert(number);
            output << "Inserted " << number << " to AVL Tree" << std::endl;
            //avlTree.printAVLTree(output);
        } else if (structureType == "HASHTABLE") {
            hashTable.insert(number);
            output << "Inserted " << number << " to Hash Table" << std::endl;
            //hashTable.printTable(output);
        } else if (structureType == "GRAPH") {
            isstr >> number2;
            graph.insertEdge(number, number2, 0);
            output << "Inserted edge (" << number << ", " << number2 << ") to Graph" << std::endl;
            //graph.printGraph(output);
        }
    } else if (action == "COMPUTESHORTESTPATH") {
        int number1, number2;
        isstr >> structureType >> number1 >> number2;
        int cost = graph.computeShortestPath(number1, number2);
        output << "Shortest path from " << number1 << " to " << number2 << " costs " << cost << std::endl;
    } else if (action == "COMPUTESPANNINGTREE") {
        isstr >> structureType;
        int cost = graph.computeSpanningTree();
        output << "Spanning tree of Graph costs  " << cost << std::endl;
    } else if (action == "FINDCONNECTEDCOMPONENTS") {
        isstr >> structureType;
        int components = graph.findConnectedComponents();
        output << "The number of connected components of Graph is  " << components << std::endl;
    }
}


int main() {
    // Initializing data structures
    MinHeap minHeap;
    MaxHeap maxHeap;
    AVLTree avlTree;
    Graph graph(10);
    HashTable hashTable(1000);

    // Opening input and output files
    std::ifstream commandsFile("commands.txt");
    std::ofstream outputFile("output.txt");

    // Error handling for file opening
    if (!commandsFile.is_open()) {
        outputFile << "Error: Could not open commands file" << std::endl;
        return 1;
    }

    if (!outputFile.is_open()) {
        outputFile << "Error: Could not open output file" << std::endl;
        return 1;
    }

    // Reading and executing commands from input file
    std::string command;
    while (std::getline(commandsFile, command)) {
        auto start = std::chrono::steady_clock::now();
        executeCommand(command, minHeap, maxHeap, avlTree, graph, hashTable, outputFile);
        auto end = std::chrono::steady_clock::now();
        // Calculating and writing execution time for each command
        std::chrono::duration<double> duration = end - start;
        outputFile << std::fixed << std::setprecision(6) << duration.count() << " sec" << std::endl;
        outputFile << std::endl;
    }

    return 0;
}
