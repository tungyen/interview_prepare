#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <convexHull.cpp>
#include <unordered_set>
using namespace std;

class Jarvis_march : public convexHull{
public:
    Jarvis_march(vector<vector<double>> &p): convexHull(p){}
    vector<Point> getConvexHull(){
        vector<Point> convexHull;
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
};

class Graham_scan: public convexHull{
public:
    Graham_scan(vector<vector<double>> &p) : convexHull(p){}
    vector<Point> getConvexHull(){
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
};

class Andrew_monotone_chain: public convexHull{
public:
    Andrew_monotone_chain(vector<vector<double>> &p) : convexHull(p){}
    bool checkSame(Point &p1, Point &p2){
        return p1.x == p2.x && p1.y == p2.y;
    }
    vector<Point> getConvexHull(){
        vector<Point> convexHullRes;
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
};

class Quick_hull: public convexHull{
public:
    Quick_hull(vector<vector<double>> &p) : convexHull(p){}

    double lineDist(Point &p1, Point &p2, Point &p){
        double cross_val = (p2.x-p1.x) * (p.y-p1.y) - (p2.y-p1.y) * (p.x-p1.x);
        return abs(cross_val);
    }

    void recursion(Point &p1, Point &p2, int &idx1, int &idx2, int side){
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

    vector<Point> getConvexHull(){
        int idx1 = 0;
        int idx2 = points.size()-1;
        recursion(points[0], points[points.size()-1], idx1, idx2, 1);
        recursion(points[0], points[points.size()-1], idx1, idx2, -1);
        return convexHullRes;
    }

private:
    unordered_set<int> s;
    vector<Point> convexHullRes;
};


