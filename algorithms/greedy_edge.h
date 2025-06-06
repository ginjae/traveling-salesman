#ifndef GREEDY_H
#define GREEDY_H

#include "tsp_solver.h"

class GreedyEdge : public TSPSolver {
public:
    void solve(const std::vector<Node>& nodes) override;
};

#endif