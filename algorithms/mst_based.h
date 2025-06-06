#ifndef MST_BASED_H
#define MST_BASED_H

#include "tsp_solver.h"

class MSTBased : public TSPSolver {
public:
    void solve(const std::vector<Node>& nodes) override;
    std::vector<std::pair<int, int>> mst_edges;
    void prim_jarnik_mst(const std::vector<Node>& nodes);
};

#endif