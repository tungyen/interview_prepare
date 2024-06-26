#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Bbox{
    int x_min;
    int x_max;
    int y_min;
    int y_max;
    double score;
};

class NMS{
public:

    float IOU(Bbox box1, Bbox box2){
        int x_min = max(box1.x_min, box2.x_min);
        int y_min = max(box1.y_min, box2.y_min);
        int x_max = min(box1.x_max, box2.x_max);
        int y_max = min(box1.y_max, box2.y_max);

        int w = max(0, x_max - x_min + 1);
        int h = max(0, y_max - y_min + 1);

        int inter = w * h;
        int area1 = (box1.x_max - box1.x_min + 1) * (box1.y_max - box1.y_min + 1);
        int area2 = (box2.x_max - box2.x_min + 1) * (box2.y_max - box2.y_min + 1);
        float iou = (float)(inter/(area1+area2-inter));
        return iou;
    }

    vector<Bbox> nms(vector<Bbox> bboxes, float thres){
        vector<Bbox> res;

        sort(bboxes.begin(), bboxes.end(), [](Bbox &box1, Bbox &box2){
            return box1.score > box2.score;
        });

        while(bboxes.size()>0){
            res.push_back(bboxes[0]);
            bboxes.erase(bboxes.begin());

            for(auto it=bboxes.begin();it != bboxes.end();){
                if(IOU(res.back(), *it) >= thres){
                    it = bboxes.erase(it);
                }
                else{
                    it++;
                }
            }
        }

        return res;
    }
};


int main()
{

    return 0;
}
