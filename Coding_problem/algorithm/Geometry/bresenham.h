#ifndef BRESENHAM_H
#define BRESENHAM_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


class Bresenham
{
public:
    class cell{
    public:
        unsigned int x;
        unsigned int y;
        cell(int x0, int y0): x(x0), y(y0){}
    };
    Bresenham();
    void getLine(int x0, int y0, int x1, int y1);
    vector<cell> getRes();
private:
    vector<cell> line;
};

#endif // BRESENHAM_H
