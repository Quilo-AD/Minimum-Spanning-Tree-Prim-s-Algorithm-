#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <chrono>

using namespace std;

// Disjoint Set / Union Find structure
class DisjointSet {
    vector<int> parent, rank;
public:
    DisjointSet(int n): parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }
    void unite(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return;
        if (rank[pu] < rank[pv]) parent[pu] = pv;
        else if (rank[pv] < rank[pu]) parent[pv] = pu;
        else {
            parent[pv] = pu;
            rank[pu]++;
        }
    }
};

struct Edge {
    int src, dest, weight;
    bool operator<(const Edge& rhs) const {
        return weight < rhs.weight;
    }
};

void kruskalMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());

    DisjointSet ds(V);
    vector<Edge> mst;
    int totalWeight = 0;

    for (const auto &edge : edges) {
        int u = edge.src, v = edge.dest;
        if (ds.find(u) != ds.find(v)) {
            ds.unite(u, v);
            mst.push_back(edge);
            totalWeight += edge.weight;
        }
    }

    cout << "Edges in MST:\n";
    for (const auto &e : mst) {
        cout << e.src << " - " << e.dest << " : " << e.weight << "\n";
    }
    cout << "Total MST Weight: " << totalWeight << "\n";
}

int main() {
    string filename;
    cout << "Enter input filename: ";
    cin >> filename;
    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Failed to open file.\n";
        return 1;
    }

    unordered_map<string, int> nodeToIndex;
    vector<string> indexToNode;
    vector<Edge> edges;
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

        Edge e = {nodeToIndex[from], nodeToIndex[to], cost};
        edges.push_back(e);
    }
    input.close();

    int V = (int)indexToNode.size();

    auto start = chrono::high_resolution_clock::now();
    kruskalMST(V, edges);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;
    cout << "Elapsed time: " << elapsed.count() << " seconds\n";

    return 0;
}

