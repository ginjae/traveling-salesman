#ifndef NODE_H
#define NODE_H

#include <cmath>

struct Node {
    int id;
    double x, y;
};

inline int euclidean_distance(const Node& a, const Node& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return (int) (std::sqrt(dx * dx + dy * dy) + 0.5);
}

#endif