#include <iostream>
#include <vector>
#include <queue>
using namespace std;

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
