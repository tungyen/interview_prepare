#include "polygon.h"

// Polygon
Polygon::Polygon(vector<vector<double>> &points){
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

double Polygon::angle(vector<double> &start, vector<double> &end){
    return atan2(end[1]-start[1], end[0]-start[0]);
}

double Polygon::getArea(){
    double area = 0.0;
    for(int i=vertex.size()-1, j = 0;j<vertex.size();i = j++){
        double cur = vertex[i][0] * vertex[j][1] - vertex[i][1]*vertex[j][0];
        area += cur;
    }
    return area;
}

vector<double> Polygon::getMassCenter(){
    double cx = 0.0;
    double cy = 0.0;
    double w = 0.0;

    for(int i=vertex.size()-1, j = 0;j<vertex.size();i = j++){
        double cross = vertex[i][0]*vertex[j][1] - vertex[i][1]*vertex[j][0];
        cx += (vertex[i][0] + vertex[j][0]) * cross;
        cy += (vertex[i][1] + vertex[j][1]) * cross;
        w += cross;
    }
    return {cx/(w*3), cy/(3*w)};
}

double Polygon::cross(vector<double> &o, vector<double> &p, vector<double> &q){
    return (p[0]-o[0]) * (q[1]-o[1]) - (p[1] - o[1]) * (q[0] - o[0]);
}

bool Polygon::checkInside(vector<double> &p){
    for(int i=vertex.size()-1, j = 0;j<vertex.size();i = j++){
        vector<double> fir = {vertex[i][0] - p[0], vertex[i][1] - p[1]};
        vector<double> sec = {vertex[j][0] - p[0], vertex[j][1] - p[1]};
        double cross = fir[0]*sec[1] - fir[1]*sec[0];
        if(cross < 0){
            return false;
        }
    }
    return true;
}

bool Polygon::checkInsideOnline(vector<double> &p){
    int l = 1;
    int r = vertex.size()-1;
    int line = -1;

    while(l < r){
        int mid = l + (r-l)/2;
        if(cross(vertex[0], p, vertex[mid]) > 0){
            line = mid;
            r = mid-1;
        }
        else{
            l = mid+1;
        }
    }
    return cross(vertex[line-1], p, vertex[line]) < 0;
}

double Polygon::interpolateX(double y, vector<double> &p1, vector<double> &p2){
    if(p1[1] == p2[1]){
        return p1[0];
    }
    return p1[0] + (p2[0]-p1[0]) * (y-p1[1]) / (p2[1]-p1[1]);
}

bool Polygon::checkOnPolygon(vector<double> &p){
    bool res = false;
    for(int i=vertex.size()-1, j = 0;j<vertex.size();i = j++){
        if((vertex[i][1] > p[1] != vertex[j][1] > p[1]) && p[0] < interpolateX(p[1], vertex[i], vertex[j])){
            res = !res;
        }
    }
    return res;
}


// Angle3D
double angle3D::computeAngle(vector<vector<double>> &points){

    vector<Point> tmp;
    for(int i = 0;i<points.size();i++){
        Point p = {points[i][0], points[i][1], points[i][2]};
        tmp.push_back(p);
    }

    Point v1 = getVector(tmp[2], tmp[0]);
    Point v2 = getVector(tmp[1], tmp[0]);

    return getAngleVector(v1, v2);

}

angle3D::Point angle3D::getVector(Point &end, Point &start){
    return {end.x-start.x, end.y-start.y, end.z-start.z};
}

double angle3D::getAngleVector(Point &v1, Point &v2){
    return atan2(CP(v1, v2), IP(v1, v2));
}

double angle3D::IP(Point &v1, Point &v2){
    return (v1.x*v2.x + v1.y*v2.y + v1.z+v2.z);
}

double angle3D::CP(Point &v1, Point &v2){
    Point cross_res = {v1.y*v2.z-v1.z*v2.y, v1.z*v2.x-v1.x-v2.z, v1.x*v2.y-v1.y*v2.x};
    double norm = sqrt(pow(cross_res.x, 2) + pow(cross_res.y, 2) + pow(cross_res.z, 2));
    return norm;
}

