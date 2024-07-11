#include <iostream>
#include <convexhull.h>
#include <polygon.h>
using namespace std;

void ConvexHullTest(){
    vector<vector<double>> points = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    vector<vector<double>> points2 = {{0, 0}, {0, 4}, {-4, 0}, {5, 0}, {0, -6}, {1, 0}};

    // Jarvis_march algorithm
    cout<<"Jarvis March Algorithm"<<endl;
    Jarvis_march jarvis = Jarvis_march(points);
    vector<Jarvis_march::Point> jarvisRes = jarvis.getConvexHull();

    for(int i = 0;i<jarvisRes.size();i++){
        cout<<jarvisRes[i].x<<" "<<jarvisRes[i].y<<endl;
    }

    // Graham Scan algorithm
    cout<<"Graham Scan Algorithm"<<endl;
    Graham_scan graham = Graham_scan(points);
    vector<Graham_scan::Point> grahamRes = jarvis.getConvexHull();

    for(int i = 0;i<grahamRes.size();i++){
        cout<<grahamRes[i].x<<" "<<grahamRes[i].y<<endl;
    }

    // Andrew Monotone Chain algorithm
    cout<<"Andrew Monotone Chain Algorithm"<<endl;
    Andrew_monotone_chain andrew = Andrew_monotone_chain(points);
    vector<Andrew_monotone_chain::Point> andrewRes = andrew.getConvexHull();

    for(int i = 0;i<andrewRes.size();i++){
        cout<<andrewRes[i].x<<" "<<andrewRes[i].y<<endl;
    }

    // Quick Hull algorithm
    cout<<"Quick Hull Algorithm"<<endl;
    Quick_hull quick = Quick_hull(points2);
    vector<Quick_hull::Point> quickRes = quick.getConvexHull();

    for(int i = 0;i<quickRes.size();i++){
        cout<<quickRes[i].x<<" "<<quickRes[i].y<<endl;
    }
}

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
    Polygon poly = Polygon(points);
}

int main()
{
    ConvexHullTest();
    polySeqTest();
    return 0;
}
