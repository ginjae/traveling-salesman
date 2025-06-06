#ifndef GREEDY_H
#define GREEDY_H

#include "tsp_solver.h"

struct Edge {
    int u, v;
    int dist;

    bool operator<(const Edge& other) const {
        return dist < other.dist;
    }
};

class GreedyEdge : public TSPSolver {
public:
    void solve(const std::vector<Node>& nodes) override;
};

#endif