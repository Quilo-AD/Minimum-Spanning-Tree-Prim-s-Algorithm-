Project Title:
Optimal Power Grid Connection using Prim’s MST Algorithm with Comparative Analysis of Kruskal’s Algorithm

Problem Statement:
The rapid expansion of electricity demand requires power transmission networks to be more efficient and cost-effective.One of the biggest challenges in optimization is designing a power grid that connects all of the substations with the shortest possible total cable length or the minimum total transmission cost and no extra loops. This project aims to create a weighted, connected graph that shows how electricity is transmitted in a region or in between regions. The vertices are substations or regions and the edges are possible transmission lines with costs or distances. The objective is to identify the most cost-effective setup or configuration that preserves complete connectivity at the lowest possible cost using Prim's Minimum Spanning Tree (MST) algorithm.

Project Overview:
This project contains two implementations of Prim's Minimum Spanning Tree algorithm in C++:

Using an adjacency matrix representation.

Using an adjacency list representation optimized for large datasets.

Both versions read graph input from text files with edges and weights, and output the MST edges and weights.

The project also contains implementation of Kruskal's Minimum Spanning Tree algorithm in C++ for comparative analysis with above both codes.It reads graph input from text files with edges and weights, and output the MST edges and weights.

The comparative analysis of working of the both implementations of Prim's MST on dense graph and sparse graph is included as well.

- adjacency_matrix_mst.cpp — Prim’s MST using adjacency matrix 
- adjacency_list_mst.cpp — Prim’s MST using adjacency list with priority queue 
- generateGraph.cpp — Generate sparse and dense graphs with user-specified node count 
- kruskal.cpp — Kruskal’s algorithm for MST 
- README.md — Project documentation 
- testcases/ — Example input test cases 


Requirements:
C++17 or later compiler (e.g., g++ or clang++)

Standard C++ libraries (no external dependencies)

Compilation Instructions:

Compile the adjacency matrix version

bash$ g++ adjacency_matrix_mst.cpp -o mst_matrix 

Compile the adjacency list version

bash$ g++ adjacency_list_mst.cpp -o mst_list 

Compile the graph generator

bash$ g++ generateGraph.cpp -o generate_graph 

Compile the kruskal version

bash$ g++ kruskal.cpp -o kruskal


Usage Instructions:

Run adjacency matrix executable and provide input file name:
$ ./mst_matrix
enter the file name: testcases/filename.txt

Run adjacency list executable and provide input file name:
$ ./mst_list
enter the file name: testcases/filename.txt

Each input file should be a text file where each line represents an edge in the format

from_node   to_node    cost
from_node and to_node can be integers or strings (depending on the version).

cost is an integer weight of the edge.

Run the graph generator executable file:
$ ./generate_graph
enter number of nodes: 4

Run kruskal executable and provide input file name:
$ ./kruskal
enter the file name: /testcases/filename.txt

Example Input and Expected Output
Example input (testcases/filename.txt)

0 1 10
1 2 5
0 2 15
Expected output (partial):

Edge    Weight
0 - 1   10
1 - 2   5

Only for the graph generator - 
Example input:

4

Expected Output(file generated):

(sparse_graph.txt)(dense_graph.txt)

Notes:
For large graphs, use the adjacency list version for better performance and memory.

The adjacency matrix version may not scale well beyond thousands of nodes.

Both versions remove isolated (disconnected) nodes automatically.



Contact:
For questions or feedback, contact: bmat2312@isibang.ac.in, bmat2218@isibang.ac.in



