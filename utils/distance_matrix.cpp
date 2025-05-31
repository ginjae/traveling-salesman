#include "distance_matrix.h"

using namespace std;

DistanceMatrix::DistanceMatrix(const vector<Node>& nodes) : n(nodes.size()) {
    this->data.resize(this->n * (this->n - 1) / 2);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            data[index(i, j, this->n)] = euclidean_distance(nodes[i], nodes[j]);
}

double DistanceMatrix::get_distance(int i, int j) const {
    if (i == j) return 0.0;
        return data[index(i, j, this->n)];
}