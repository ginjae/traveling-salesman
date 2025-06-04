#include "held_karp.h"

#include <climits>

using namespace std;

#include <iostream>
void HeldKarp::solve(const vector<Node>& nodes) {
    size_t n = nodes.size();
    map<pair<set<int>, int>, int> parent;
    for (int k = 0; k < n; k++) {
        set<int> base_set = { 0, k };
        dp[{ base_set, k }] = euclidean_distance(nodes[0], nodes[k]);
        parent[{ base_set, k }] = 0;
    }
    
    for (int s = 3; s <= n; s++) {
        vector<set<int>> combinations;
        set<int> cur = { 0 };
        generate_combinations(cur, 1, n, s, combinations);

        for (const set<int>& comb: combinations) {
            for (const int& c : comb) {
                if (c == 0) continue;

                set<int> prev_comb = comb;
                prev_comb.erase(c);

                int min_dist = INT_MAX;
                int best_prev = -1;
                for (const int& p : prev_comb) {
                    if (p == c) continue;
                    auto iter = dp.find({ prev_comb, p });
                    if (iter != dp.end()) {
                        int dist = iter->second + euclidean_distance(nodes[p], nodes[c]);
                        min_dist = min(min_dist, dist);
                        best_prev = p;
                    }
                }
                dp[{ comb, c }] = min_dist;
                parent[{ comb, c }] = best_prev; 
            }
        }
    }

    set<int> full_set;
    for (int i = 0; i < n; i++) full_set.insert(i);
    
    int min_total_distance = INT_MAX;
    int last_node = -1;
    for (int k = 1; k < n; k++) {
        int dist = dp[{ full_set, k }] + euclidean_distance(nodes[k], nodes[0]);
        min_total_distance = min(min_total_distance, dist);
        last_node = k;
    }

    set<int> cur_set = full_set;
    int cur_node = last_node;
    this->solution = vector<int>(n);
    for (int i = n - 1; i >= 0; i--) {
        this->solution[i] = cur_node;
        int prev_node = parent[{ cur_set, cur_node }];
        cur_set.erase(cur_node);
        cur_node = prev_node;
    }
    this->solution.push_back(0);
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
