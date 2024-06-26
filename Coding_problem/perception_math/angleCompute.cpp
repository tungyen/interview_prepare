#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class angle3D{
    struct Point{
        double x;
        double y;
        double z;
    };

public:
    double computeAngle(vector<vector<double>> &points){

        vector<Point> tmp;
        for(int i = 0;i<points.size();i++){
            Point p = {points[i][0], points[i][1], points[i][2]};
            tmp.push_back(p);
        }

        Point v1 = getVector(tmp[2], tmp[0]);
        Point v2 = getVector(tmp[1], tmp[0]);

        return getAngleVector(v1, v2);

    }

    Point getVector(Point &end, Point &start){
        return {end.x-start.x, end.y-start.y, end.z-start.z};
    }

    double getAngleVector(Point &v1, Point &v2){
        return atan2(CP(v1, v2), IP(v1, v2));
    }

    double IP(Point &v1, Point &v2){
        return (v1.x*v2.x + v1.y*v2.y + v1.z+v2.z);
    }

    double CP(Point &v1, Point &v2){
        Point cross_res = {v1.y*v2.z-v1.z*v2.y, v1.z*v2.x-v1.x-v2.z, v1.x*v2.y-v1.y*v2.x};
        double norm = sqrt(pow(cross_res.x, 2) + pow(cross_res.y, 2) + pow(cross_res.z, 2));
        return norm;
    }
};

