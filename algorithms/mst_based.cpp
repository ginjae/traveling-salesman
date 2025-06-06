#include "mst_based.h"

#include <climits>
#include <queue>
#include <stack>

using namespace std;

void MSTBased::solve(const vector<Node>& nodes) {
    size_t n = nodes.size();

    // Build MST using Prim's algorithm
    this->prim_jarnik_mst(nodes);

    // Build the MST as an adjacency list
    vector<vector<int>> mst(n);
    for (const auto& [u, v] : this->mst_edges) {
        mst[u].push_back(v);
        mst[v].push_back(u);
    }

    // Pre-order traversal to generate TSP tour
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

void MSTBased::prim_jarnik_mst(const vector<Node>& nodes) {
    size_t n = nodes.size();
    vector<bool> in_mst(n, false);
    vector<int> min_distance(n, INT_MAX);
    vector<int> parent(n, -1);

    // (distance, node index)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    // Start from node index 0
    min_distance[0] = 0;
    pq.emplace(0, 0);

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (in_mst[u])
            continue;

        in_mst[u] = true;

        for (int v = 0; v < n; v++) {
            if (!in_mst[v]) {
                int distance = euclidean_distance(nodes[u], nodes[v]);
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
