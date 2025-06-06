#include "held_karp.h"

#include <climits>
#include <bit>

using namespace std;

void HeldKarp::solve(const vector<Node>& nodes) {
    size_t n = nodes.size();
    map<pair<set<int>, int>, int> dp;       // minimum distance
    map<pair<set<int>, int>, int> parent;   // previous node

    // Initialize base cases
    for (int k = 1; k < n; k++) {
        set<int> base_set = { 0, k };
        dp[{ base_set, k }] = euclidean_distance(nodes[0], nodes[k]);
        parent[{ base_set, k }] = 0;
    }
    
    // Compute dp
    for (int s = 3; s <= n; s++) {
        vector<set<int>> combinations;
        set<int> cur = { 0 };
        generate_combinations(cur, 1, n, s, combinations);

        for (const set<int>& comb: combinations) {
            for (const int& c : comb) {
                if (c == 0) continue;

                set<int> prev_comb = comb;
                prev_comb.erase(c);
                int best_cost = INT_MAX;
                int best_prev = -1;

                for (const int& p : prev_comb) {
                    if (p == c) continue;
                    auto iter = dp.find({ prev_comb, p });
                    if (iter != dp.end()) {
                        int cost = iter->second + euclidean_distance(nodes[p], nodes[c]);
                        if (cost < best_cost) {
                            best_cost = min(best_cost, cost);
                            best_prev = p;
                        }
                    }
                }

                if (best_prev != -1) {
                    dp[{ comb, c }] = best_cost;
                    parent[{ comb, c }] = best_prev; 
                }
            }
        }
    }

    set<int> full_set;
    for (int i = 0; i < n; i++) full_set.insert(i);
    
    // Find the distance of optimal solution and the last node of it
    int best_cost = INT_MAX;
    int last_node = -1;
    for (int k = 1; k < n; k++) {
        int tour_cost = dp[{ full_set, k }] + euclidean_distance(nodes[k], nodes[0]);
        if (tour_cost < best_cost) {
            best_cost = tour_cost;
            last_node = k;
        }
    }

    // Backtrack to store the optimal path
    this->solution.resize(n + 1, 0);
    set<int> cur_set = full_set;
    int cur_node = last_node;
    for (int i = n - 1; i >= 0; i--) {
        this->solution[i] = cur_node;
        int prev_node = parent[{ cur_set, cur_node }];
        cur_set.erase(cur_node);
        cur_node = prev_node;
    }
    this->solution[n] = 0;
}

void HeldKarp::generate_combinations(set<int> cur, int start, int n, int s, vector<set<int>>& result) {
    if (cur.size() == s) {
        result.push_back(cur);
        return;
    }

    for (int i = start; i < n; i++) {
        cur.insert(i);
        generate_combinations(cur, i + 1, n, s, result);
        cur.erase(i);
    }
}


/* For this function, LLM is used to convert std::set-based subset handling to bitmask representation */
void HeldKarpBitmask::solve(const vector<Node>& nodes) {
    int n = nodes.size();

    const int FULL = (1 << n) - 1;           // Bitmask containing all nodes

    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));    // minimum distance
    vector<vector<int>> parent(1 << n, vector<int>(n, -1));     // previous node

    // Initialize base cases: mask = {0, k} (k = 1 ... n-1)
    for (int k = 1; k < n; k++) {
        int mask = (1 << 0) | (1 << k);
        dp[mask][k] = euclidean_distance(nodes[0], nodes[k]);
        parent[mask][k] = 0;
    }

    // Compute dp
    for (int s = 3; s <= n; s++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (((mask & 1) == 0) || (__builtin_popcount(mask) != s))
                continue;
            for (int j = 1; j < n; j++) {
                if (!((mask >> j) & 1)) continue;

                int prev_mask = mask ^ (1 << j);
                int best_cost = INT_MAX;
                int best_prev = -1;

                for (int p = 1; p < n; p++) {
                    if (!((prev_mask >> p) & 1)) continue;
                    int cost = dp[prev_mask][p];
                    if (cost >= INT_MAX) continue;

                    cost += euclidean_distance(nodes[p], nodes[j]);
                    if (cost < best_cost) {
                        best_cost = cost;
                        best_prev = p;
                    }
                }

                if (best_prev != -1) {
                    dp[mask][j] = best_cost;
                    parent[mask][j] = best_prev;
                }
            }
        }
    }

    // Find the distance of optimal solution and the last node of it
    int min_total_distance = INT_MAX;
    int last_node = -1;
    int full = FULL;
    for (int k = 1; k < n; k++) {
        if (dp[full][k] >= INT_MAX) continue;
        int tour_cost = dp[full][k] + euclidean_distance(nodes[k], nodes[0]);
        if (tour_cost < min_total_distance) {
            min_total_distance = tour_cost;
            last_node = k;
        }
    }

    // Backtrack to store the optimal path
    this->solution.resize(n + 1, 0);
    int mask = full;
    int cur_node = last_node;
    for (int i = n - 1; i >= 0; i--) {
        this->solution[i] = cur_node;
        int prev = parent[mask][cur_node];
        mask = mask ^ (1 << cur_node);
        cur_node = prev;
    }
    this->solution[n] = 0;
}
