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


// Prim's MST using adjacency list
// graph[u] contains pairs (v, weight)
void primMST(const vector<vector<pair<int, int>>> &graph, const vector<string> &indexToNode) {
    int V = (int)graph.size();

    vector<int> parent(V, -1);
    vector<int> key(V, INT_MAX);
    vector<bool> inMST(V, false);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    // Start from vertex 0 (arbitrary choice) we can take another argument startnode and start with it
    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        for (auto &[v, weight] : graph[u]) {
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++) {
        if (parent[i] != -1)
            cout << indexToNode[parent[i]] << " - " << indexToNode[i] << " \t" << key[i] << "\n";
    }

    // After MST generation
    int edgeCount = 0;
    int totalWeight = 0;

    for (int i = 0; i < V; i++) {
        if (parent[i] != -1) {
            edgeCount++;
            totalWeight += key[i];
        }
    }

    // Verify MST properties
    cout << "\nMST Verification:" << endl;
    cout << "Expected number of edges: " << (V - 1) << endl;
    cout << "Actual number of edges: " << edgeCount << endl;
    cout << "Total weight of MST: " << totalWeight << endl;

    // Connectivity check
    bool allConnected = true;
    for (int i = 0; i < V; i++) {
        if (!inMST[i]) { allConnected = false; break; }
    }
    cout << "All vertices connected? " << (allConnected ? "Yes" : "No") << endl;
}

int main() {
    string filename;
    cout<<"enter file name: ";
    cin>>filename;
    ifstream input(filename);
    //Make sure file contains three columns , starting node, ending node and weight of the edge
    if (!input.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    unordered_map<string, int> nodeToIndex;
    vector<string> indexToNode;
    vector<tuple<int, int, int>> edges; // storing edges as (u, v, weight)

    string line;
    while (getline(input, line)) {
        istringstream iss(line);
        string from, to;
        int cost;
        if (!(iss >> from >> to >> cost)) continue;

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

    // Building adjacency list
    vector<vector<pair<int,int>>> graph(V);

    for (auto &[u, v, cost] : edges) {
        graph[u].emplace_back(v, cost);
        graph[v].emplace_back(u, cost); // undirected graph
    }

    cout << "Graph loaded with " << V << " nodes and " << edges.size() << " edges.\n";
    auto start = chrono::high_resolution_clock::now();
    // code to measure

    primMST(graph, indexToNode);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "\nElapsed time: " << diff.count() << " s"<<endl;

    return 0;
}

