#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <set>
using namespace std;

// Generate synthetic weighted undirected graph and save to file.
void generateGraph(int n, int m, const string &filename) {
    srand(time(0));
    set<pair<int, int>> edges;
    ofstream fout(filename);

    // Ensure the graph is connected by first forming a chain
    for (int i = 1; i < n; i++) {
        int w = rand() % 100 + 1;  // random weight 1–100
        fout << i - 1 << " " << i << " " << w << "\n";
        edges.insert({min(i - 1, i), max(i - 1, i)});
    }

    // Add remaining edges for density
    while (edges.size() < m) {
        int u = rand() % n;
        int v = rand() % n;
        if (u == v) continue;
        if (edges.count({min(u, v), max(u, v)})) continue;
        int w = rand() % 100 + 1;
        fout << u << " " << v << " " << w << "\n";
        edges.insert({min(u, v), max(u, v)});
    }

    fout.close();
    cout << "Generated graph with " << n << " nodes and " << edges.size() << " edges.\n";
}

int main() {
    int n = 100;   // number of nodes
    cout<<"enter number of nodes: ";
    cin>>n;
    int m_sparse = 2 * n;         // sparse graph (~2 edges per node)
    int m_dense = n * (n - 1) / 4; // dense graph (~half of full)

    generateGraph(n, m_sparse, n+"sparse_graph.txt");
    generateGraph(n, m_dense, n+"dense_graph.txt");

    return 0;
}

