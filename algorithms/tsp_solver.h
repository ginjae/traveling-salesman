#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include "node.h"

#include <vector>

class TSPSolver {
public:
    std::vector<int> solution;

    /*
     * Saves the approximate solution of TSP.
     * Input:       Vector of nodes
     * Solution:    TSP tour as a sequence of node indices
                    (starting and ending at node 0)
    */
    virtual void solve(const std::vector<Node>& nodes) = 0;

    /* Returns the total distance of the solution */
    int get_total_distance(const std::vector<Node>& nodes) {
        int total = 0;
        for (size_t i = 1; i < this->solution.size(); i++)
            total += euclidean_distance(nodes[this->solution[i - 1]], nodes[this->solution[i]]);
        return total;
    }
};

#endif