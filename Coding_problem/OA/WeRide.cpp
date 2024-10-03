#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

int distinctCombination(vector<int> &capacity, long desireCap){
    // input: {1, 2, 2, 2, 4}, 8 => 3
    // input: {-1, 9, -3, -9, 1, 3}, -27 => 4

    unordered_map<int, vector<int>> mp;
    unordered_set<string> s;
    int n = capacity.size();
    for(int i = 0;i<n-1;i++){
        mp[capacity[i]*capacity[i+1]].push_back(i);
    }

    for(int i = 0;i<n;i++){
        long target = desireCap / capacity[i];
        if(!mp.count(target)){
            continue;
        }
        for(auto &pos:mp[target]){
            if(i == pos || i == pos+1){
                continue;
            }
            string str = i<pos ? to_string(i)+","+to_string(pos)+","+to_string(pos+1) : to_string(pos)+","+to_string(pos+1)+","+to_string(i);
            s.insert(str);
        }
    }
    return s.size();
}

void dijkstra(int source, vector<vector<int>> &adj, vector<vector<int>> &res, vector<bool> &vis){
    vis[source] = true;
    queue<int> q;
    q.push(source);
    int curStep = 0;

    while(!q.empty()){
        int s = q.size();
        while(s--){
            int cur = q.front();
            vis[cur] = true;
            q.pop();
            res[source][cur] = curStep;
            for(int &next:adj[cur]){
                if(vis[next]){continue;}
                q.push(next);
            }
        }
        curStep++;
    }
}

vector<vector<int>> getDijkstraTable(vector<vector<int>> &adj){
    vector<vector<int>> res(adj.size(), vector<int>(adj.size(), -1));
    for(int i = 0;i<adj.size();i++){
        vector<bool> vis(adj.size(), false);
        dijkstra(i, adj, res, vis);
    }
    return res;
}

int getStepFromSpecificVis(int n, vector<vector<int>> &edges, vector<int> &mustPass){
    // Input: 5, {{0, 1}, {0, 2}, {2, 3}, {2, 4}}, {1, 3} => 6
    vector<vector<int>> adj(n, vector<int>());
    for(auto &edge:edges){
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]);
    }
    int ans = INT_MAX;
    vector<vector<int>> dijkstraTable = getDijkstraTable(adj);
    sort(mustPass.begin(), mustPass.end());

    do{
        int step = 0;
        step += dijkstraTable[0][mustPass[0]];
        for(int i = 0;i<mustPass.size()-1;i++){
            step += dijkstraTable[mustPass[i]][mustPass[i+1]];
        }
        step += dijkstraTable[mustPass.back()][n-1];
        ans = min(ans, step);

    }while(next_permutation(mustPass.begin(), mustPass.end()));
    return ans;
}

void test1(){
    vector<int> cap1 = {1, 2, 2, 2, 4};
    long desireCap1 = 8;
    vector<int> cap2 = {-1, 9, -3, -9, 1, 3};
    long desireCap2 = -27;
    cout<<"Answer of the first test in Q1: "<<3<<", the output is: "<<distinctCombination(cap1, desireCap1)<<endl;
    cout<<"Answer of the second test in Q1: "<<4<<", the output is: "<<distinctCombination(cap2, desireCap2)<<endl;
}

void test2(){
    int n1 = 5;
    vector<vector<int>> edges1 = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};
    vector<int> mustPass1 = {1, 3};
    int res1 = getStepFromSpecificVis(n1, edges1, mustPass1);
    cout<<"Answer of the first test in Q3: "<<6<<", the output is: "<<res1<<endl;
}
