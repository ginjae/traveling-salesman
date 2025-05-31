#ifndef DISTANCE_MATRIX_H
#define DISTANCE_MATRIX_H

#include "node.h"

#include <vector>
#include <cmath>

inline int index(int i, int j, int n) {
    if (i == j) return 0;
    if (i < j)
        return i * n - (i * (i + 1)) / 2 + (j - i - 1);
    else
        return j * n - (j * (j + 1)) / 2 + (i - j - 1);
}

inline double euclidean_distance(const Node& a, const Node& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

class DistanceMatrix {
private:
    int n;
    std::vector<double> data;
public:
    DistanceMatrix(const std::vector<Node>& nodes);
    double get_distance(int i, int j) const;
};

#endif