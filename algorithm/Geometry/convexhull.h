#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_set>
using namespace std;


class ConvexHull
{
public:
    struct Point{
        double x;
        double y;
    };
    vector<Point> points;
    ConvexHull(vector<vector<double>> &p);
    int cross(Point &o, Point &p1, Point &p2);
    double getDist(Point &p1, Point &p2);
    bool checkFar(Point &o, Point &a, Point &b);
    bool compare(Point a, Point b);
};

class Jarvis_march : public ConvexHull{
public:
    Jarvis_march(vector<vector<double>> &p): ConvexHull(p){}
    vector<Point> getConvexHull();
};


class Graham_scan: public ConvexHull{
public:
    Graham_scan(vector<vector<double>> &p) : ConvexHull(p){}
    vector<Point> getConvexHull();
};


class Andrew_monotone_chain: public ConvexHull{
public:
    Andrew_monotone_chain(vector<vector<double>> &p) : ConvexHull(p){}
    bool checkSame(Point &p1, Point &p2);
    vector<Point> getConvexHull();
};

class Quick_hull: public ConvexHull{
public:
    Quick_hull(vector<vector<double>> &p) : ConvexHull(p){}

    double lineDist(Point &p1, Point &p2, Point &p);
    void recursion(Point &p1, Point &p2, int &idx1, int &idx2, int side);
    vector<Point> getConvexHull();

private:
    unordered_set<int> s;
    vector<Point> convexHullRes;
};



#endif // CONVEXHULL_H
