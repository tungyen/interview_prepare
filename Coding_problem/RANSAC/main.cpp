#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace std;


void ransacFit(const vector<cv::Point2f> &points, cv::Vec4f &line, int maxIteration=1000,
               double sigma=1.0, double k_min=-7, double k_max=7)
{
    unsigned int n = points.size();
    if(n < 2){
        return;
    }


    cv::RNG rng;
    double bestScore = -1.;
    for(int i=0;i<maxIteration;i++){
        int idx1 = 0;
        int idx2 = 0;

        while(idx1 == idx2){
            idx1 = rng(n);
            idx2 = rng(n);
        }

        cv::Point2f p1 = points[idx1];
        cv::Point2f p2 = points[idx2];

        cv::Point2f diff = p2 - p1;
        diff *= 1 / norm(diff);
        double score = 0;

        if(diff.y/diff.x > k_min && diff.y/diff.x < k_max){
            for(int i=0;i<n;i++){
                cv::Point2f v = points[i] - p1;
                double error = v.y*diff.x - v.x*diff.y;
                if(fabs(error) < sigma){
                    score++;
                }
            }
        }

        if(score > bestScore){
            bestScore = score;
            line = cv::Vec4f(diff.x, diff.y, p1.x, p1.y);
        }
    }
}

int main()
{
    int h = 720;
    int w = 1280;
    cv::Mat image(h,w,CV_8UC3,cv::Scalar(125,125,125));

    // Defining a lane parameter
    double k = -0.6432/0.7657;
    double b = 548 - k*534;

    vector<cv::Point2f> points;

    for (int i = h/2; i < h; i+=10)
    {
        cv::Point2f point(int((i-b)/k),i);
        points.push_back(point);
    }

    // Adding random noise on the straight line
    cv::RNG rng((unsigned)time(NULL));
    for (int i = h/2; i < h; i+=10)
    {
        int x = int((i-b)/k);
        x = rng.uniform(x-10,x+10);
        int y = i;
        y = rng.uniform(y-30,y+30);
        cv::Point2f point(x,y);
        points.push_back(point);
    }

    // Adding noise
    for (int i = 0; i < h; i+=20)
    {
        int x = rng.uniform(1,640);
        int y = rng.uniform(1,h/2);

        cv::Point2f point(x,y);
        points.push_back(point);
    }

    int n = points.size();
    for (int j = 0; j < n; ++j)
    {
        cv::circle(image,points[j],5,cv::Scalar(0,0,0),-1);
    }

    //RANSAC fitting
    cv::Vec4f lineParam;
    ransacFit(points, lineParam, 1000, 10);
    double k_res = lineParam[1] / lineParam[0];
    double b_res = lineParam[3] - k_res*lineParam[2];

    cv::Point p1, p2;
    p1.y = 720;
    p1.x = ( p1.y - b_res) / k_res;

    p2.y = 360;
    p2.x = (p2.y-b_res) / k_res;

    cv::line(image, p1, p2, cv::Scalar(0,255,0),2);
    cv::imshow("image", image);
    cv::waitKey(0);

    return 0;
}
