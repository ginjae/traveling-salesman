#ifndef JAM_H
#define JAM_H

#include "tsp_solver.h"

class Jam : public TSPSolver {
public:
    void solve(const std::vector<Node>& nodes) override;
};

#endif
