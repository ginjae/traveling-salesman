#include "greedy_edge.h"
#include "union_find.h"

#include <algorithm>
#include <set>

using namespace std;

void GreedyEdge::solve(const vector<Node>& nodes) {
    int n = nodes.size();
    vector<Edge> edges;
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Edge e{i, j, euclidean_distance(nodes[i], nodes[j])};
            edges.push_back(e);
        }
    }
    sort(edges.begin(), edges.end());

    vector<int> degree(n, 0);
    UnionFind uf(n);
    vector<pair<int, int>> tour_edges;

    // Select minimum distance edge that makes no cycle
    for (auto& e : edges) {
        if (degree[e.u] >= 2 || degree[e.v] >= 2)
            continue;
        if (tour_edges.size() == n - 1 || uf.find_parent(e.u) != uf.find_parent(e.v)) {
            tour_edges.push_back({e.u, e.v});
            uf.union_parent(e.u, e.v);
            degree[e.u]++;
            degree[e.v]++;
        }
    }

    // Form a cycle
    for (auto& e : edges) {
        if (degree[e.u] == 1 && degree[e.v] == 1 && uf.find_parent(e.u) == uf.find_parent(e.v)) {
            tour_edges.push_back({e.u, e.v});
            break;
        }
    }

    // Construct Path
    vector<set<int>> graph(n);
    for (auto& e : tour_edges) {
        graph[e.first].insert(e.second);
        graph[e.second].insert(e.first);
    }

    vector<bool> visited(n, false);
    int cur = 0;
    this->solution.push_back(cur);
    visited[cur] = true;

    while (this->solution.size() < n) {
        int next = *graph[cur].begin();
        graph[cur].erase(next);
        graph[next].erase(cur);
        this->solution.push_back(next);
        visited[next] = true;
        cur = next;
    }

    this->solution.push_back(this->solution[0]);
}
