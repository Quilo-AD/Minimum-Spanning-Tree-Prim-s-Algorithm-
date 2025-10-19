#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <chrono>
#include <queue>

using namespace std;

// Helper function to find the vertex with minimum key value not yet included in MST
int minKey(const vector<int> &key, const vector<bool> &mstSet) {
    int minVal = INT_MAX;
    int min_index = -1;

    for (int v = 0; v < static_cast<int>(mstSet.size()); v++) {
        if (!mstSet[v] && key[v] < minVal) {
            minVal = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print edges of the MST with their weights
void printMST(const vector<int> &parent, const vector<vector<int>> &graph, const vector<string> &indexToNode) {
    cout << "Edge \tWeight\n";
    for (int i = 1; i < (int)graph.size(); i++) {
        if (parent[i] != -1 && graph[parent[i]][i] != -1) {
            cout << indexToNode[parent[i]] << " - " << indexToNode[i] << " \t" << graph[parent[i]][i] << "\n";
        }
    }
}

// Function to verify MST connectivity using adjacency matrix and BFS traversal
void verifyConnectivityWithMatrix(const vector<int> &parent, const vector<vector<int>> &graph) {
    int V = (int)graph.size();

    // Construct MST adjacency matrix from parent array
    vector<vector<int>> mstMatrix(V, vector<int>(V, -1));
    for (int i = 1; i < V; i++) {
        if (parent[i] != -1) {
            mstMatrix[i][parent[i]] = graph[i][parent[i]];
            mstMatrix[parent[i]][i] = graph[parent[i]][i];
        }
    }

    // BFS traversal to check connectivity in MST
    vector<bool> visited(V, false);
    queue<int> q;
    q.push(0);
    visited[0] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < V; v++) {
            if (mstMatrix[u][v] != -1 && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    // Check if all vertices were visited
    bool allConnected = true;
    for (bool v : visited) {
        if (!v) {
            allConnected = false;
            break;
        }
    }
    cout << "All vertices connected? " << (allConnected ? "Yes" : "No") << endl;
}

// Prim's algorithm implementation for MST using adjacency matrix
void primMST(const vector<vector<int>> &graph, const vector<string> &indexToNode) {
    int V = (int)graph.size();

    vector<int> parent(V, -1);       // Stores MST structure
    vector<int> key(V, INT_MAX);     // Key values used to pick minimum weight edge
    vector<bool> mstSet(V, false);   // Vertices included in MST

    key[0] = 0;                      // Start from first vertex

    // Loop to construct MST with V-1 edges
    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);    // Pick min key vertex not yet included
        if (u == -1) {
            cout << "Warning: Graph appears disconnected — MST covers only reachable vertices.\n";
            break;
        }
        mstSet[u] = true;            // Include vertex u in MST

        // Update key values of adjacent vertices of u
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != -1 && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph, indexToNode);       // Display resulting MST edges
    verifyConnectivityWithMatrix(parent, graph); // Verify MST connectivity
}

int main() {
    string filename;
    cout << "enter file name: ";
    cin >> filename;

    ifstream input(filename);

    if (!input.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    unordered_map<string, int> nodeToIndex;      // Map nodes to indices
    vector<string> indexToNode;                   // Reverse mapping
    vector<tuple<int, int, int>> edges;           // Store edges as (from, to, cost)

    string line;
    while (getline(input, line)) {
        istringstream iss(line);
        string from, to;
        int cost;
        if (!(iss >> from >> to >> cost)) continue;

        // Map from string nodes to numeric indices
        if (nodeToIndex.find(from) == nodeToIndex.end()) {
            nodeToIndex[from] = (int)indexToNode.size();
            indexToNode.push_back(from);
        }
        if (nodeToIndex.find(to) == nodeToIndex.end()) {
            nodeToIndex[to] = (int)indexToNode.size();
            indexToNode.push_back(to);
        }

        int fromIdx = nodeToIndex[from];
        int toIdx = nodeToIndex[to];
        edges.emplace_back(fromIdx, toIdx, cost);
    }
    input.close();

    int V = (int)indexToNode.size();

    // Build adjacency matrix with initial values -1 (no edge)
    vector<vector<int>> adjMatrix(V, vector<int>(V, -1));

    // Populate adjacency matrix with edge costs
    for (auto &[fromIdx, toIdx, cost] : edges) {
        adjMatrix[fromIdx][toIdx] = cost;
        adjMatrix[toIdx][fromIdx] = cost;  // Undirected graph
    }

    cout << "Adjacency matrix created. Computing MST...\n";

    auto start = chrono::high_resolution_clock::now();
    primMST(adjMatrix, indexToNode);            // Run MST algorithm
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> diff = end - start;
    cout << "\nElapsed time: " << diff.count() << " s" << endl;

    return 0;
}

