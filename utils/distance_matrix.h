#ifndef DISTANCE_MATRIX_H
#define DISTANCE_MATRIX_H

#include "node.h"

#include <vector>
#include <cmath>

class DistanceMatrix {
private:
    std::vector<std::vector<int>> data;
public:
    DistanceMatrix() {}
    DistanceMatrix(const std::vector<Node>& nodes) {
        size_t n = nodes.size();
        this->data.resize(n * n);
        for (int i = 0; i < n; i++)
            this->data[i][i] = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                int d = euclidean_distance(nodes[i], nodes[j]);
                this->data[i][j] = d;
                this->data[j][i] = d;
            }
    }
    int get_distance(int i, int j) const { return this->data[i][j]; }
    int size() const { return this->data.size(); }
};

#endif