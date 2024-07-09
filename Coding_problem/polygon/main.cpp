#include <iostream>
#include <cstdlib>
using namespace std;
#include "angle3D.cpp"
#include "polygon.cpp"

double angleTest(){
    vector<vector<double>> points;
    for(int i=0;i<3;i++){
        vector<double> p = {double(i), pow(i,2), pow(i, 3)};
        points.push_back(p);
    }

    angle3D ang = angle3D();
    double res = ang.computeAngle(points);
    cout<<"The angle is: "<<res<<endl;
    return res;
}

double polySeqTest(){
    vector<vector<double>> points = {{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0.5, 0.5}};
    polygon poly = polygon(points);
}

int main()
{
    polySeqTest();
    return 0;
}
