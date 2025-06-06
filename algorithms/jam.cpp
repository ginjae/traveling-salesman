#include "jam.h"
#include "union_find.h"

#include <queue>
#include <algorithm>
#include <set>

using namespace std;

struct EdgeCompare {
    bool operator()(Edge const& a, Edge const& b) const {
        if (a.dist != b.dist)
            return a.dist < b.dist;
        if (a.u != b.u)
            return a.u > b.u;
        return a.v > b.v;
    }
};

#include <iostream>
void Jam::solve_with_topk(const vector<Node>& nodes, int k) {
    int n = nodes.size();
    vector<Edge> edges;
    
    // Build priority queue sorted by descending distance (max heap)
    priority_queue<Edge, vector<Edge>, EdgeCompare> pq;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Edge e{i, j, euclidean_distance(nodes[i], nodes[j])};
            if (pq.size() < k)
                pq.push(e);
            else {  // if pq has k elements
                const Edge& longest_edge = pq.top();
                // if current edge is shorter than longest edge in pq
                if (e.dist < longest_edge.dist) {
                    // swap
                    pq.pop();
                    pq.push(e);
                }
            }
        }
    }
    edges.resize(pq.size());
    for (int i = pq.size() - 1; i >= 0; i--) {
        edges[i] = pq.top();
        pq.pop();
    }

    // for (auto e : edges)
    //     cout << e.u << ", " << e.v << ": " << e.dist << endl;
    cout << edges.size() << endl;

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

    // If there are (n-1) edges in "edges", then
    // Form a cycle
    if (tour_edges.size() == n - 1) {
        for (auto& e : edges) {
            if (degree[e.u] == 1 && degree[e.v] == 1 && uf.find_parent(e.u) == uf.find_parent(e.v)) {
                tour_edges.push_back({e.u, e.v});
                break;
            }
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

    // Repeat until all nodes are visited
    while (this->solution.size() < (size_t)n) {
        int next = -1;
        // If there is still a connected neighbor node in "graph", use it first
        if (!graph[cur].empty()) {
            next = *graph[cur].begin();
            graph[cur].erase(next);
            graph[next].erase(cur);
        }
        else {
            // No more neighbors remain in graph[cur],
            // So find the unvisited node closest to cur and connect to it
            double bestDist = std::numeric_limits<double>::infinity();
            for (int v = 0; v < n; v++) {
                if (!visited[v]) {
                    double d = euclidean_distance(nodes[cur], nodes[v]);
                    if (d < bestDist) {
                        bestDist = d;
                        next = v;
                    }
                }
            }
            // If next is -1 (all nodes have already been visited), break out of the loop
            if (next < 0) break;
        }

        this->solution.push_back(next);
        visited[next] = true;
        cur = next;
    }

    this->solution.push_back(this->solution[0]);
}
