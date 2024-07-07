#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


class convexHull{
public:
    struct Point{
        double x;
        double y;
    };

    convexHull(vector<vector<double>> &p){
        sort(p.begin(), p.end());
        for(int i = 0;i<p.size();i++){
            points.push_back({p[i][0], p[i][1]});
        }
    }

    int cross(Point &o, Point &p1, Point &p2){
        double cross_val = (p1.x-o.x) * (p2.y-o.y) - (p1.y-o.y) * (p2.x-o.x);
        if(cross_val == 0){return 0;}
        return cross_val > 0 ? 1 : -1;
    }

    double getDist(Point &p1, Point &p2){
        return sqrt(pow(p1.x-p2.x, 2) + pow(p1.y-p2.y, 2));
    }

    bool checkFar(Point &o, Point &a, Point &b){
        return getDist(o, a) < getDist(o, b);
    }

    bool compare(Point a, Point b){
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    }
    vector<Point> points;
};
