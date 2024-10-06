#include <iostream>
#include <vector>
#include <deque>

using namespace std;

vector<vector<float>> avgPooling(vector<vector<float>> &matrix, int k=2, int stride=1, int pad=0){

    // Check padding
    if(pad != 0){
        matrix.push_back(vector<float>(matrix[0].size(), 0));
        matrix.insert(matrix.begin(), vector<float>(matrix[0].size(), 0));
        for(int i = 0;i<matrix.size();i++){
            matrix[i].push_back(0);
            matrix[i].insert(matrix[i].begin(), 0);
        }
    }

    int h = matrix.size();
    int w = matrix[0].size();

    // Create the dp table
    vector<vector<float>> dp(h, vector<float>(w, 0));
    for(int i = 0;i<h;i++){
        for(int j = 0;j<w;j++){
            dp[i][j] = matrix[i][j];
            if(i != 0){
                dp[i][j] += dp[i-1][j];
            }
            if(j != 0){
                dp[i][j] += dp[i][j-1];
            }
            if(i != 0 && j != 0){
                dp[i][j] -= dp[i-1][j-1];
            }
        }
    }

    int out_h = (h-k)/stride + 1;
    int out_w = (w-k)/stride + 1;

    vector<vector<float>> res(out_h, vector<float>(out_w, 0));

    for(int i = 0;i<out_h;i++){
        for(int j = 0;j<out_w;j++){
            int start_y = i*stride;
            int start_x = j*stride;
            int end_y = start_y + k-1;
            int end_x = start_x + k-1;
            float area = dp[end_y][end_x];
            if(start_x != 0 && start_y != 0){
                area += dp[start_y-1][start_x-1];
            }
            if(start_x != 0){
                area -= dp[end_y][start_x-1];
            }
            if(start_y != 0){
                area -= dp[start_y-1][end_x];
            }
            res[i][j] = area / (k*k);
        }
    }
    return res;
}

void getMaxRow(vector<float> &vec, int k, int stride, vector<float> &res){
    deque<int> q;
    for(int i = 0;i<vec.size();i++){
        while(!q.empty() && vec[q.back()] < vec[i]){
            q.pop_back();
        }
        q.push_back(i);
        if(!q.empty() && q.front() <= i-k){
            q.pop_front();
        }

        if(i >= k-1 && (i-k+1) % stride == 0){
            res.push_back(vec[q.front()]);
        }
    }
}

void getMaxCol(vector<vector<float>> &matrix, int col, int k, int stride, vector<float> &res){
    deque<int> q;
    for(int i = 0;i<matrix.size();i++){
        while(!q.empty() && matrix[q.back()][col] < matrix[i][col]){
            q.pop_back();
        }
        q.push_back(i);
        if(!q.empty() && q.front() <= i-k){
            q.pop_front();
        }

        if(i >= k-1 && (i-k+1) % stride == 0){
            res.push_back(matrix[q.front()][col]);
        }
    }
}

vector<vector<float>> maxPooling(vector<vector<float>> &matrix, int k=2, int stride=1, int pad=0){
    // Check padding
    if(pad != 0){
        matrix.push_back(vector<float>(matrix[0].size(), 0));
        matrix.insert(matrix.begin(), vector<float>(matrix[0].size(), 0));
        for(int i = 0;i<matrix.size();i++){
            matrix[i].push_back(0);
            matrix[i].insert(matrix[i].begin(), 0);
        }
    }

    int h = matrix.size();
    int w = matrix[0].size();

    int out_h = (h-k)/stride + 1;
    int out_w = (w-k)/stride + 1;

    // Operate on the row
    vector<vector<float>> res;
    for(int i = 0;i<h;i++){
        vector<float> tmp;
        getMaxRow(matrix[i], k, stride, tmp);
        res.push_back(tmp);
    }

    // Operate on the col
    vector<vector<float>> ans(out_h, vector<float>(out_w, 0));
    for(int i = 0;i<out_w;i++){
        vector<float> tmp;
        getMaxCol(matrix, i, k, stride, tmp);
        for(int j = 0;j<tmp.size();j++){
            ans[j][i] = tmp[j];
        }
    }
    return ans;
}

void avgTest(){
    vector<vector<float>> matrix = {{1,1,1,1}, {2,2,2,2},{3,3,3,3},{4,4,4,4}};
    vector<vector<float>> res = avgPooling(matrix, 2, 2);
    for(int i = 0;i<res.size();i++){
        for(int j = 0;j<res[0].size();j++){
            cout<<res[i][j]<<" ";
        }
        cout<<endl;
    }
}

void maxTest(){
    vector<vector<float>> matrix = {{1,1,1,1}, {2,2,2,2},{3,3,3,3},{4,4,4,4}};
    vector<vector<float>> res = maxPooling(matrix, 2, 2);
    for(int i = 0;i<res.size();i++){
        for(int j = 0;j<res[0].size();j++){
            cout<<res[i][j]<<" ";
        }
        cout<<endl;
    }
}
