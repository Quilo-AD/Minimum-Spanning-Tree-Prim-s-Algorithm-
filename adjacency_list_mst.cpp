#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <climits>
#include <chrono>

using namespace std;

// Function to verify MST properties and connectivity after MST is generated
void verifyConnectivityWithMatrix(const vector<int> &parent, vector<int> &key, vector<bool> &inMST) {
    int edgeCount = 0;       // Count edges included in MST
    int totalWeight = 0;     // Sum of weights of MST edges
    int V = (int)parent.size();

    // Counting edges and summing weights based on parent vector and key values
    for (int i = 0; i < V; i++) {
        if (parent[i] != -1) {
            edgeCount++;
            totalWeight += key[i];
        }
    }

    // Display MST verification results
    cout << "\nMST Verification:" << endl;
    cout << "Expected number of edges: " << (V - 1) << endl;
    cout << "Actual number of edges: " << edgeCount << endl;
    cout << "Total weight of MST: " << totalWeight << endl;

    // Check if all vertices are connected (included in MST)
    bool allConnected = true;
    for (int i = 0; i < V; i++) {
        if (!inMST[i]) {
            allConnected = false;
            break;
        }
    }
    cout << "All vertices connected? " << (allConnected ? "Yes" : "No") << endl;
}

// Prim's MST implementation using adjacency list
// The graph is represented as vector of vectors of pairs (neighbor, edge weight)
void primMST(const vector<vector<pair<int, int>>> &graph, const vector<string> &indexToNode) {
    int V = (int)graph.size();

    vector<int> parent(V, -1);      // Store MST structure (parent of each node)
    vector<int> key(V, INT_MAX);    // Store minimum edge weight to each node
    vector<bool> inMST(V, false);   // Track vertices included in MST

    // Min-heap (priority queue) to select vertex with minimum key at each step
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    // Initialize the first vertex: key=0, add to queue
    key[0] = 0;
    pq.push({0, 0});

    // Loop until all vertices included or queue becomes empty
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) 
            continue;           // Ignore if already included in MST

        inMST[u] = true;        // Mark vertex u as included

        // Update key values for adjacent vertices
        for (auto &[v, weight] : graph[u]) {
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});   // Add updated vertex to priority queue
            }
        }
    }

    // Print the edges of MST with corresponding weights
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++) {
        if (parent[i] != -1)
            cout << indexToNode[parent[i]] << " - " << indexToNode[i] << " \t" << key[i] << "\n";
    }

    // Verify MST edge count, weight sum, and connectivity
    verifyConnectivityWithMatrix(parent, key, inMST);
}

int main() {
    string filename;
    cout << "Enter file name: ";
    cin >> filename;

    ifstream input(filename);
    // Input file must contain three columns: start_node, end_node, edge_weight
    if (!input.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    unordered_map<string, int> nodeToIndex;   // Map node names to integer indices
    vector<string> indexToNode;                // Map indices back to node names
    vector<tuple<int, int, int>> edges;        // Store edges (u, v, cost)

    string line;
    while (getline(input, line)) {
        istringstream iss(line);
        string from, to;
        int cost;
        if (!(iss >> from >> to >> cost)) 
            continue;    // Skip invalid lines

        // Map nodes to indices if not already mapped
        if (nodeToIndex.find(from) == nodeToIndex.end()) {
            nodeToIndex[from] = (int)indexToNode.size();
            indexToNode.push_back(from);
        }
        if (nodeToIndex.find(to) == nodeToIndex.end()) {
            nodeToIndex[to] = (int)indexToNode.size();
            indexToNode.push_back(to);
        }

        int u = nodeToIndex[from];
        int v = nodeToIndex[to];
        edges.emplace_back(u, v, cost);
    }
    input.close();

    int V = (int)indexToNode.size();

    // Build adjacency list representation of the graph
    vector<vector<pair<int,int>>> graph(V);

    for (auto &[u, v, cost] : edges) {
        graph[u].emplace_back(v, cost);
        graph[v].emplace_back(u, cost); // undirected graph, add both ways
    }

    cout << "Graph loaded with " << V << " nodes and " << edges.size() << " edges.\n";

    // Measure time to compute MST using Prim's algorithm
    auto start = chrono::high_resolution_clock::now();

    primMST(graph, indexToNode);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "\nElapsed time: " << diff.count() << " s" << endl;

    return 0;
}

