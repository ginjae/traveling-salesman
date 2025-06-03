#ifndef HELD_KARP_H
#define HELD_KARP_H

#include "tsp_solver.h"

class HeldKarp : public TSPSolver {
public:
    void solve(const std::vector<Node>& nodes) override;
};

#endif