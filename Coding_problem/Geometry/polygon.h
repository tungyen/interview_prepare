#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;



class Polygon
{
public:
    Polygon(vector<vector<double>> &points);
    double angle(vector<double> &start, vector<double> &end);
    double getArea();
    vector<double> getMassCenter();
    double cross(vector<double> &o, vector<double> &p, vector<double> &q);
    bool checkInside(vector<double> &p);
    bool checkInsideOnline(vector<double> &p);
    double interpolateX(double y, vector<double> &p1, vector<double> &p2);
    bool checkOnPolygon(vector<double> &p);


private:
    vector<vector<double>> vertex;
    vector<double> center;
};


class angle3D{
    struct Point{
        double x;
        double y;
        double z;
    };

public:
    double computeAngle(vector<vector<double>> &points);
    Point getVector(Point &end, Point &start);
    double getAngleVector(Point &v1, Point &v2);
    double IP(Point &v1, Point &v2);
    double CP(Point &v1, Point &v2);
};

#endif // POLYGON_H
