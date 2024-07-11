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

