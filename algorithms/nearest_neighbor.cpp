#include "nearest_neighbor.h"

#include <climits>
#include <random>
#include <queue>

using namespace std;

void NearestNeighbor::solve(const vector<Node>& nodes) {
    int n = nodes.size();
    vector<bool> visited(n, false);
    int current = 0;
    visited[current] = true;
    this->solution.push_back(current);

    for (int step = 1; step < n; ++step) {
        int min_dist = INT_MAX;
        int next = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && euclidean_distance(nodes[current], nodes[i]) < min_dist) {
                min_dist = euclidean_distance(nodes[current], nodes[i]);
                next = i;
            }
        }
        visited[next] = true;
        this->solution.push_back(next);
        current = next;
    }

    this->solution.push_back(this->solution[0]);
}

void RandomizedNearestNeighbor::solve_with_topk_random(const vector<Node>& nodes, int k) {
    int n = nodes.size();
    vector<bool> visited(n, false);
    int current = 0;
    visited[current] = true;
    this->solution.push_back(current);

    random_device rd;
    mt19937 gen(rd());

    for (int step = 1; step < n; ++step) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> candidates;
        for (int i = 0; i < n; i++)
            if (!visited[i])
                candidates.emplace(euclidean_distance(nodes[current], nodes[i]), i);

        int top_k = min(k, (int)candidates.size());
        uniform_int_distribution<> dis(0, top_k - 1);
        int pops = dis(gen);
        for (int i = 0; i < pops; i++)
            candidates.pop();
        int chosen = candidates.top().second;

        visited[chosen] = true;
        this->solution.push_back(chosen);
        current = chosen;
    }

    this->solution.push_back(this->solution[0]);
}
