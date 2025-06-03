#ifndef HELD_KARP_H
#define HELD_KARP_H

#include "tsp_solver.h"

class Held_Karp : public TSP_Solver {
public:
    void solve(const std::vector<Node>& nodes) override;
};

#endif