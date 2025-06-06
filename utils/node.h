#ifndef NODE_H
#define NODE_H

#include <cmath>

struct Node {
    int id;
    double x, y;
};

struct Edge {
    int u, v;
    int dist;

    bool operator<(const Edge& other) const {
        if (this->dist == other.dist) {
            if (this->u == other.u)
                return this->v > other.v;
            return this->u > other.u;
        }
        return this->dist < other.dist;
    }
};

inline int euclidean_distance(const Node& a, const Node& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return (int) (std::sqrt(dx * dx + dy * dy) + 0.5);
}

#endif