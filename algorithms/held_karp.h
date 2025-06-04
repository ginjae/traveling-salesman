#ifndef HELD_KARP_H
#define HELD_KARP_H

#include "tsp_solver.h"

#include <map>
#include <set>

class HeldKarp : public TSPSolver {
public:
    void solve(const std::vector<Node>& nodes) override;
    std::map<std::pair<std::set<int>, int>, int> dp;
    void generate_combinations(std::set<int> cur, int start, int n, int s, std::vector<std::set<int>>& result);
};

#endif