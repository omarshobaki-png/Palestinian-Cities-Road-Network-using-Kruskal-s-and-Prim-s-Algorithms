# Palestinian Cities Road Network (Prim's and Kruskal's Algorithms in C)

Author: Omar Shoubaki  
Birzeit University  
Electrical and Computer Engineering Department

## Project Overview
This project simulates a road network between Palestinian cities and applies two minimum spanning tree (MST) algorithms — **Prim’s Algorithm** and **Kruskal’s Algorithm** — to find the minimum total distance required to connect all the cities.

The program reads city connections (roads) from a text file, builds a weighted graph, and allows the user to apply either algorithm to generate and compare their results in terms of total cost and execution time.

## How It Works
The program starts with a menu that allows the user to:
1. Load cities and roads from a text file  
2. Apply Prim’s Algorithm  
3. Apply Kruskal’s Algorithm  
4. Compare both algorithms  
5. Exit  

When the data is loaded, the program stores cities and their connections as a graph where:
- Each city is a vertex.  
- Each road (with its distance) is an edge.  

Users can then apply either Prim’s or Kruskal’s algorithm to generate an MST and calculate the total cost of connecting all cities.

## Features
1. Load cities  
   Reads all city names and road connections from a file named `cities.txt`.  
2. Apply Prim’s Algorithm  
   Finds the MST starting from a user-specified city using Prim’s approach.  
3. Apply Kruskal’s Algorithm  
   Finds the MST using Kruskal’s approach with union–find for cycle detection.  
4. Compare both algorithms  
   Executes both algorithms and displays their total cost and execution time side by side.  
5. Exit  
   Exits the program.

## Data Structures Used
1. Graph Structure  
   Stores cities, edges, and distances between them.  
2. Edge Array  
   Represents all roads as edge connections between cities with corresponding weights.  
3. Union-Find Structure  
   Used in Kruskal’s Algorithm to efficiently detect and avoid cycles.  
4. Heap (Min-Heap) 
   Used to efficiently retrieve the smallest edge in Kruskal’s Algorithm.

## File Format
Input File: `cities.txt`  
Each line in the file represents a road connection between two cities with a given distance, using the following format:
city1#city2#distance
Example:
Ramallah#Nablus#50
Ramallah#Jerusalem#35
Nablus#Jenin#40
Hebron#Jericho#70

## How to Run
1. Make sure `cities.txt` is in the same directory as the source file.  
2. Compile the program using any C compiler
3. Run the program
4. Follow the on-screen menu to load the cities and apply algorithms.

## Example Menu
Please select an operation 1-5:

1)Load cities

2)Apply Prim's Algorithm

3)Apply Kruskal's Algorithm

4)Compare both Algorithms

5)Exit


## Algorithm Details
### Prim’s Algorithm
- Starts from a user-specified city.  
- Adds the smallest available edge that connects a new city to the growing MST.  
- Keeps track of connected cities and total cost.  

### Kruskal’s Algorithm
- Sorts all edges by distance using a min-heap.  
- Iteratively adds the smallest edge that does not create a cycle.  
- Uses the union–find data structure to manage connected components.  

## Output
For each algorithm, the program prints:
- The edges included in the MST.  
- The total cost (sum of all distances in the MST).  
- The execution time (in seconds).  


## Concepts Demonstrated
- Graph representation and traversal  
- Minimum Spanning Tree algorithms (Prim’s and Kruskal’s)  
- Heap operations (heapify, buildMinHeap, getMin)  
- Union–find operations (find and mergeSets)  
- File parsing using `strtok`  
- Time complexity and performance comparison  

## Purpose
This project was developed as part of the COMP2421 – Data Structures course to demonstrate practical implementation of graph-based algorithms (Prim’s and Kruskal’s) for solving real-world network optimization problems.
