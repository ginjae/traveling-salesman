#include "mst_based.h"

#include <limits>
#include <queue>
#include <stack>

using namespace std;

void MST_Based::solve(const vector<Node>& nodes) {
    size_t n = nodes.size();
    // Step 1: Build MST using Prim's algorithm
    this->prim_jarnik_mst(nodes);
    // Step 2: Build the MST as an adjacency list
    vector<vector<int>> mst(n);
    for (const auto& [u, v] : this->mst_edges) {
        mst[u].push_back(v);
        mst[v].push_back(u);
    }
    // Step 3: Pre-order traversal to generate TSP tour
    vector<bool> visited(n);
    stack<int> s;
    s.push(0);

    while (!s.empty()) {
        int u = s.top();
        s.pop();

        if (visited[u])
            continue;

        visited[u] = true;
        this->solution.push_back(u);

        const vector<int>& neighbors = mst[u];
        for (const int& neighbor : neighbors) {
            if (!visited[neighbor]) {
                s.push(neighbor);
            }
        }
    }

    this->solution.push_back(this->solution[0]);
}

void MST_Based::prim_jarnik_mst(const vector<Node>& nodes) {
    size_t n = nodes.size();
    vector<bool> in_mst(n, false);
    vector<double> min_distance(n, numeric_limits<double>::max());
    vector<int> parent(n, -1);

    // (distance, node index)
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;

    // Starts from node index 0
    min_distance[0] = 0.0;
    pq.emplace(0.0, 0);

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (in_mst[u])
            continue;

        in_mst[u] = true;

        for (int v = 0; v < n; v++) {
            if (!in_mst[v]) {
                double distance = euclidean_distance(nodes[u], nodes[v]);
                if (distance < min_distance[v]) {
                    min_distance[v] = distance;
                    parent[v] = u;
                    pq.emplace(distance, v);
                }
            }
        }
    }

    for (int i = 1; i < n; i++)
        if (parent[i] != -1)
            this->mst_edges.emplace_back(parent[i], i);
}