#include "convexhull.h"

ConvexHull::ConvexHull(vector<vector<double>> &p){
    sort(p.begin(), p.end());
    for(int i = 0;i<p.size();i++){
        points.push_back({p[i][0], p[i][1]});
    }
}

int ConvexHull::cross(Point &o, Point &p1, Point &p2){
    double cross_val = (p1.x-o.x) * (p2.y-o.y) - (p1.y-o.y) * (p2.x-o.x);
    if(cross_val == 0){return 0;}
    return cross_val > 0 ? 1 : -1;
}

double ConvexHull::getDist(Point &p1, Point &p2){
    return sqrt(pow(p1.x-p2.x, 2) + pow(p1.y-p2.y, 2));
}

bool ConvexHull::checkFar(Point &o, Point &a, Point &b){
    return getDist(o, a) < getDist(o, b);
}

bool ConvexHull::compare(Point a, Point b){
    return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}


// Jarvish
vector<ConvexHull::Point> Jarvis_march::getConvexHull(){
    vector<ConvexHull::Point> convexHull;
    convexHull.push_back(points[0]);
    int current = 0;

    while(true){
        int next = current;
        for(int i = 0;i<points.size();i++){

            int val = cross(convexHull.back(), points[i], points[next]);
            if(val > 0 || (val == 0 && !checkFar(convexHull.back(), points[i], points[next]))){
                next = i;
            }
        }
        if(next == 0){
            break;
        }
        convexHull.push_back(points[next]);
        current = next;
    }
    return convexHull;
}

// Graham
vector<ConvexHull::Point> Graham_scan::getConvexHull(){
    // Initialize the vector of convex hull result
    vector<Point> convexHullRes;
    convexHullRes.push_back(points[0]);

    // Sort the other points based on the first point
    sort(points.begin()+1, points.end(), [this](Point &p1, Point &p2) {
        int val = cross(points[0], p1, p2);
        return val > 0 || (val == 0 && getDist(points[0], p1) < getDist(points[0], p2));
    });

    // Start Graham Scan algorithm
    for(int i = 1;i<points.size();i++){
        while(convexHullRes.size() >= 2 && cross(convexHullRes[convexHullRes.size()-2], convexHullRes[convexHullRes.size()-1], points[i])<=0){
            convexHullRes.pop_back();
        }
        convexHullRes.push_back(points[i]);
    }
    return convexHullRes;
}


// Andrew Monotone
bool Andrew_monotone_chain::checkSame(Point &p1, Point &p2){
    return p1.x == p2.x && p1.y == p2.y;
}
vector<ConvexHull::Point> Andrew_monotone_chain::getConvexHull(){
    vector<ConvexHull::Point> convexHullRes;
    convexHullRes.push_back(points[0]);
    convexHullRes.push_back(points[1]);

    for(int i = 2;i<points.size();i++){
        while(convexHullRes.size() >= 2 && cross(convexHullRes[convexHullRes.size()-2], convexHullRes[convexHullRes.size()-1], points[i])<=0){
            convexHullRes.pop_back();
        }
        convexHullRes.push_back(points[i]);
    }
    convexHullRes.pop_back();
    for(int i = points.size()-1;i>=0;i--){
        while(convexHullRes.size() >= 2 && cross(convexHullRes[convexHullRes.size()-2], convexHullRes[convexHullRes.size()-1], points[i])<=0){
            convexHullRes.pop_back();
        }
        convexHullRes.push_back(points[i]);
    }
    sort(convexHullRes.begin(), convexHullRes.end(), [this](Point &p1, Point &p2) {
        return (p1.x < p2.x) || (p1.x == p2.x && p1.y < p2.y);
    });
    int idx = 1;
    while(idx < convexHullRes.size()){
        if(checkSame(convexHullRes[idx], convexHullRes[idx-1])){
            convexHullRes.erase(convexHullRes.begin()+idx);
        }
        else{idx++;}
    }
    return convexHullRes;
}

// Quick Hull
double Quick_hull::lineDist(Point &p1, Point &p2, Point &p){
    double cross_val = (p2.x-p1.x) * (p.y-p1.y) - (p2.y-p1.y) * (p.x-p1.x);
    return abs(cross_val);
}

void Quick_hull::recursion(Point &p1, Point &p2, int &idx1, int &idx2, int side){
    int idx = -1;
    double maxDist = 0;

    for(int i = 0;i<points.size();i++){
        double dist = lineDist(p1, p2, points[i]);
        if(cross(p1, p2, points[i]) == side && dist > maxDist){
            idx = i;
            maxDist = dist;
        }
    }

    if(idx == -1){
        if(!s.count(idx1)){
            s.insert(idx1);
            convexHullRes.push_back(p1);
        }
        if(!s.count(idx2)){
            s.insert(idx2);
            convexHullRes.push_back(p2);
        }
        return;
    }

    recursion(p1, points[idx], idx1, idx, -cross(p1, points[idx], p2));
    recursion(points[idx], p2, idx, idx2, -cross(points[idx], p2, p1));
}

vector<ConvexHull::Point> Quick_hull::getConvexHull(){
    int idx1 = 0;
    int idx2 = points.size()-1;
    recursion(points[0], points[points.size()-1], idx1, idx2, 1);
    recursion(points[0], points[points.size()-1], idx1, idx2, -1);
    return convexHullRes;
}

