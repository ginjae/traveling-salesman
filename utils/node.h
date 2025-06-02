#ifndef NODE_H
#define NODE_H

#include <cmath>

class Node {
public:
    int id;
    double x, y;
};

inline double euclidean_distance(const Node& a, const Node& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

#endif