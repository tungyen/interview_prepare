#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;



class polygon{

public:
    polygon(vector<vector<double>> &points){
        vertex = points;
        center = vector<double>(2, 0);
        for(int i=0;i<points.size();i++){
            for(int j = 0;j<2;j++){
                center[j] += points[i][j] / points.size();
            }
        }

        sort(vertex.begin(), vertex.end(), [this](std::vector<double>& a, std::vector<double>& b) {
            return angle(center, a) < angle(center, b);
        });

        for(int i=0;i<points.size();i++){
            cout<<vertex[i][0]<<" "<<vertex[i][1]<<endl;
        }
    }

    double angle(vector<double> &start, vector<double> &end){
        return atan2(end[1]-start[1], end[0]-start[0]);
    }


private:
    vector<vector<double>> vertex;
    vector<double> center;
};
