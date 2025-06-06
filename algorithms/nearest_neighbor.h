#ifndef NEAREST_NEIGHBOR_H
#define NEAREST_NEIGHBOR_H

#include "tsp_solver.h"

class NearestNeighbor : public TSPSolver {
public:
    void solve(const std::vector<Node>& nodes) override;
};

class RandomizedNearestNeighbor : public TSPSolver {
public:
    void solve(const std::vector<Node>& nodes) override {
        solve_with_topk_random(nodes, 3);
    }
    void solve_with_topk_random(const std::vector<Node>& nodes, int k);
};

#endif