#ifndef HELD_KARP_H
#define HELD_KARP_H

#include "tsp_solver.h"

#include <map>
#include <set>

class HeldKarp : public TSPSolver {
public:
    void solve(const std::vector<Node>& nodes) override;
    void generate_combinations(std::set<int> cur, int start, int n, int s, std::vector<std::set<int>>& result);
};

class HeldKarpBitmask : public TSPSolver {
public:
    void solve(const std::vector<Node>& nodes) override;
};

#endif