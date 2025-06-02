#include "mst_based.h"

#include <unordered_map>
#include <unordered_set>
#include <stack>

using namespace std;

void MST_Based::solve(const vector<Node>& nodes) {
    // if (nodes.size() < 10'000) {    // case 1: # of nodes < 10,000
    //     // Step 0: Build Distance Matrix
    //     DistanceMatrix dist_matrix(nodes);
    //     // Step 1: Build MST using Prim's algorithm
    //     this->prim_jarnik_mst(dist_matrix);
    // } else {                        // case 2: # of nodes >= 10,000
    //     // Step 1: Build MST using Prim's algorithm
    //     this->prim_jarnik_mst(nodes);
    // }

    // Step 1: Build MST using Prim's algorithm
    this->prim_jarnik_mst(nodes);
    // Step 2: Build the MST as an adjacency list
    unordered_map<int, vector<int>> tree;
    for (const auto& [u, v] : this->mst_edges) {
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    // Step 3: Pre-order traversal to generate TSP tour
    std::unordered_set<int> visited;
    std::stack<int> s;
    s.push(0);

    while (!s.empty()) {
        int u = s.top();
        s.pop();

        if (visited.count(u)) continue;
        visited.insert(u);
        this->solution.push_back(u);

        auto& neighbors = tree[u];
        for (auto it = neighbors.rbegin(); it != neighbors.rend(); it++) {
            if (!visited.count(*it)) {
                s.push(*it);
            }
        }
    }

    this->solution.push_back(this->solution[0]);
}

void MST_Based::prim_jarnik_mst(const DistanceMatrix& dist_matrix) {
    int n = dist_matrix.size();
    vector<bool> in_mst(n, false);
    vector<double> min_distance(n, numeric_limits<double>::max());
    vector<int> parent(n, -1);

    // (node_index, distance)
    priority_queue<pair<int, double>, vector<pair<int, double>>, greater<>> pq;

    // Starts from node index 0
    min_distance[0] = 0.0;
    pq.emplace(0, 0.0);

    while (!pq.empty()) {
        int u = pq.top().first;
        pq.pop();
        if (in_mst[u])  continue;
        in_mst[u] = true;

        for (int v = 0; v < n; v++) {
            if (!in_mst[v]) {
                double distance = dist_matrix.get_distance(u, v);
                if (distance < min_distance[v]) {
                    min_distance[v] = distance;
                    parent[v] = u;
                    pq.emplace(v, distance);
                }
            }
        }
    }

    for (int i = 1; i < n; i++)
        if (parent[i] != -1)
            this->mst_edges.emplace_back(parent[i], i);
}

void MST_Based::prim_jarnik_mst(const vector<Node>& nodes) {
    int n = nodes.size();
    vector<bool> in_mst(n, false);
    vector<double> min_distance(n, numeric_limits<double>::max());
    vector<int> parent(n, -1);

    // (node_index, distance)
    priority_queue<pair<int, double>, vector<pair<int, double>>, greater<>> pq;

    // Starts from node index 0
    min_distance[0] = 0.0;
    pq.emplace(0, 0.0);

    while (!pq.empty()) {
        int u = pq.top().first;
        pq.pop();
        if (in_mst[u])  continue;
        in_mst[u] = true;

        for (int v = 0; v < n; v++) {
            if (!in_mst[v]) {
                double distance = euclidean_distance(nodes[u], nodes[v]);
                if (distance < min_distance[v]) {
                    min_distance[v] = distance;
                    parent[v] = u;
                    pq.emplace(v, distance);
                }
            }
        }
    }

    for (int i = 1; i < n; i++)
        if (parent[i] != -1)
            this->mst_edges.emplace_back(parent[i], i);
}