#ifndef JAM_H
#define JAM_H

#include "tsp_solver.h"
#include "greedy_edge.h"

#include <cmath>

class Jam : public TSPSolver {
public:
    GreedyEdge ge;
    void solve(const std::vector<Node>& nodes) override {
        int n = nodes.size();
        if (n < 10'000) {
            ge.solve(nodes);
            this->solution = ge.solution;
        }
        else
            this->solve_with_topk(nodes, nodes.size() * std::log(nodes.size()));
    }
    void solve_with_topk(const std::vector<Node>& nodes, int k);
};

#endif
