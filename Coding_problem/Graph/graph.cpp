#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class UnionFind{
public:
    UnionFind(int n){
        edge_num = 0;
        parent = vector<int>(n);
        iota(begin(parent), end(parent), 0);
        size = vector<int>(n, 1);
    }

    int find(int x){
        if(parent[x] == x){
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    int getEdges(){
        return edge_num;
    }

    bool merge(int x, int y){
        int p_x = find(x);
        int p_y = find(y);

        if(p_x == p_y){
            return false;
        }
        edge_num++;
        if(size[p_x] > size[p_y]){
            parent[p_y] = p_x;
        }
        else{
            parent[p_x] = p_y;
        }
        return true;
    }

private:
    int edge_num;
    vector<int> parent;
    vector<int> size;
};
