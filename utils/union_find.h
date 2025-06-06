#include <vector>

class UnionFind {
private:
    std::vector<int> parent, rank;
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for(int i = 0; i < n; i++) parent[i] = i;
    }

    int find_parent(int x) {
        if(parent[x] != x)
            parent[x] = find_parent(parent[x]);
        return parent[x];
    }

    void union_parent(int x, int y) {
        int root_x = find_parent(x);
        int root_y = find_parent(y);
        if(root_x == root_y)
            return;
        if(rank[root_x] < rank[root_y])
            parent[root_x] = root_y;
        else if(rank[root_x] > rank[root_y])
            parent[root_y] = root_x;
        else {
            parent[root_y] = root_x;
            rank[root_x]++;
        }
        return;
    }
};
