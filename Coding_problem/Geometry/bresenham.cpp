
#include "bresenham.h"

Bresenham::Bresenham(){

}

void Bresenham::getLine(int x0, int y0, int x1, int y1){
    if(line.size() > 0){
        line.clear();
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    unsigned int abs_dx = abs(dx);
    unsigned int abs_dy = abs(dy);

    int offset_dx = dx > 0 ? 1 : -1;
    int offset_dy = dy > 0 ? 1 : -1;
    cell tmp = cell(x0, y0);
    line.push_back(tmp);

    if(abs_dx >= abs_dy){
        int error = -abs_dx;
        for(int i = 0;i<abs_dx;i++){
            tmp.x += offset_dx;
            error += 2*abs_dy;
            if(error > 0){
                tmp.y += offset_dy;
                error -= 2*abs_dx;
            }
            line.push_back(tmp);
        }
    }
    else{
        int error = -abs_dy;
        for(int i = 0;i<abs_dy;i++){
            tmp.y += offset_dy;
            error += 2*abs_dy;
            if(error > 0){
                tmp.x += offset_dx;
                error -= 2*abs_dy;
            }
            line.push_back(tmp);
        }
    }
}

vector<Bresenham::cell> Bresenham::getRes(){
    return line;
}

