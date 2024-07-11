#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <numeric>
using namespace std;

class Node{
public:
    int val;
    vector<Node*> neighbors;
    Node(int v):val(v), neighbors(vector<Node*>()){}
    Node(int v, vector<Node*> n):val(v), neighbors(n){}
};

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

class graph_clone{
public:
    graph_clone(){}

    Node* dfs(Node* node, unordered_map<Node*, Node*> &mp){
        vector<Node*> neighbors;
        Node* tmp = new Node(node->val);

        for(auto n:node->neighbors){
            if(mp.count(n)){
                neighbors.push_back(mp[n]);
            }
            else{
                neighbors.push_back(dfs(n, mp));
            }
        }
        tmp->neighbors = neighbors;
        return tmp;
    }

    Node* clone(Node* node){
        unordered_map<Node*, Node*> mp;
        if(!node || node->neighbors.size()==0){
            return node;
        }

        return dfs(node, mp);
    }
};

class course_select{

public:
    course_select(int course_num, vector<vector<int>> &requirement): courseNum(course_num), prerequisite(requirement){}

    vector<int> getCourseSequence(){
        vector<int> indegrees(courseNum, 0);
        vector<vector<int>> adjTable(courseNum);
        vector<int> res;

        queue<int> q;

        for(auto p:prerequisite){
            adjTable[p[1]].push_back(p[0]);
            indegrees[p[0]]++;
        }

        for(int i = 0;i<courseNum;i++){
            if(indegrees[i] == 0){
                q.push(i);
            }
        }

        while(!q.empty()){
            int cur = q.front();
            q.pop();
            res.push_back(cur);
            for(int n:adjTable[cur]){
                indegrees[n]--;
                if(indegrees[n] == 0){
                    q.push(n);
                }
            }
        }
        return res;
    }

private:
    int courseNum;
    vector<vector<int>> prerequisite;
};

class shortest_bridge{
public:
    shortest_bridge(vector<vector<int>>& A):grid(A){}
    int getRes() {
        queue<pair<int, int>> q;
        bool found = false;
        for (int i = 0; i < grid.size() && !found; ++i)
            for (int j = 0; j < grid[0].size() && !found; ++j)
                if (grid[i][j]) {
                    dfs(grid, j, i, q);
                    found = true;
                }

        int steps = 0;
        vector<int> dirs{0, 1, 0, -1, 0};
        while (!q.empty()) {
            size_t size = q.size();
            while (size--) {
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                for (int i = 0; i < 4; ++i) {
                    int tx = x + dirs[i];
                    int ty = y + dirs[i + 1];
                    if (tx < 0 || ty < 0 || tx >= grid[0].size() || ty >= grid.size() || grid[ty][tx] == 2) continue;
                    if (grid[ty][tx] == 1) return steps;
                    grid[ty][tx] = 2;
                    q.emplace(tx, ty);
                }
            }
            ++steps;
        }
        return -1;
    }
private:
    void dfs(vector<vector<int>>& A, int x, int y, queue<pair<int, int>>& q) {
        if (x < 0 || y < 0 || x >= A[0].size() || y >= A.size() || A[y][x] != 1) return;
        A[y][x] = 2;
        q.emplace(x, y);
        dfs(A, x - 1, y, q);
        dfs(A, x, y - 1, q);
        dfs(A, x + 1, y, q);
        dfs(A, x, y + 1, q);
    }
    vector<vector<int>>& grid;
};
