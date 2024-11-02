#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>

using namespace std;

class TarjanSCC{

public:

    TarjanSCC(string path){
        graph = vector<vector<int>>(V);
        visited = vector<bool>(V, false);
        vertex = vector<pair<int, int>>(V);
        ifstream in(path);

        int u;
        int v;

        while(in >> u >> v){
            graph[u-1].push_back(v-1);
        }

    }

    void dfs(int source){
        if(visited[source]){
            return;
        }
        visited[source] = true;
        st.push(source);
        vertex[source] = {timestamp, timestamp};
        timestamp++;
        for(int i = 0;i<graph[source].size();i++){
            dfs(graph[source][i]);
        }

        bool change = false;
        for(int i = 0;i<graph[source].size();i++){
            if(vertex[source].second > vertex[graph[source][i]].second){
                change = true;
                vertex[source].second = vertex[graph[source][i]].second;
            }
        }
        if(!change){
            vector<int> sccTmp;
            while(!st.empty()){
                sccTmp.push_back(st.top());
                st.pop();
                if(sccTmp.back() == source){
                    break;
                }
            }
            finalSCC.push_back(sccTmp);
        }
    }

    vector<vector<int>> getSCC(){

        for(int i = 0;i<V;i++){
            dfs(i);
        }
        return finalSCC;
    }



private:
    int V = 875714;
    int timestamp = 1;
    vector<vector<int>> graph;
    vector<pair<int, int>> vertex;
    vector<bool> visited;
    stack<int> st;
    vector<vector<int>> finalSCC;
};

int main(){
    TarjanSCC tjscc = TarjanSCC("SCC.txt");
    vector<vector<int>> finalSCC = tjscc.getSCC();
    for(int i = 0;i<finalSCC.size();i++){
        cout<<"The "<<i+1<<" set of SCC is: "<<endl;;
        for(int j = 0;j<finalSCC[i].size();j++){
            if(j==0){
                cout<<finalSCC[i][j];
            }
            else{
               cout<<" "<<finalSCC[i][j];
            }
        }
        cout<<endl;
    }
    return 0;
}
