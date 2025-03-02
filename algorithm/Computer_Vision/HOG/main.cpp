#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

class HOG{

public:
    HOG(int cell=8, int block_ratio=2, int bins=9):cell_size(cell), block_size(block_ratio), bin_size(bins){}
    void HOG_descriptor(Mat &src, vector<float> &hog_descriptor){
        vector<Mat> rgb(3);

        split(src, rgb);
        Mat gx[3], gy[3];
        for (int i = 0; i < 3; ++i) {
            Sobel(rgb[i], gx[i], CV_32F, 1, 0, 1);
            Sobel(rgb[i], gy[i], CV_32F, 0, 1, 1);
        }

        Mat magnitude(src.rows, src.cols, CV_32F, Scalar(0));
        Mat angle(src.rows, src.cols, CV_32F, Scalar(0));
        for (int y = 0; y < src.rows; y++) {
            for (int x = 0; x < src.cols; x++) {
                float maxMag = 0;
                float maxAngle = 0;
                for (int i = 0; i < 3; ++i) {
                    float mag = sqrt(gx[i].at<float>(y, x) * gx[i].at<float>(y, x) + gy[i].at<float>(y, x) * gy[i].at<float>(y, x));
                    float ang = atan2(gy[i].at<float>(y, x), gx[i].at<float>(y, x)) * 180 / CV_PI;
                    if (mag > maxMag) {
                        maxMag = mag;
                        maxAngle = ang;
                    }
                }
                magnitude.at<float>(y, x) = maxMag;
                angle.at<float>(y, x) = maxAngle;
            }
        }

        int cellCountX = src.cols / cell_size;
        int cellCountY = src.rows / cell_size;
        int blockSizeX = block_size * cell_size;
        int blockSizeY = block_size * cell_size;
        int blockStride = cell_size;
        int blockCountX = (cellCountX - block_size + 1);
        int blockCountY = (cellCountY - block_size + 1);
        int descriptorSize = blockCountX * blockCountY * block_size * block_size * bin_size;
        hog_descriptor.resize(descriptorSize, 0);


        vector<vector<vector<float>>> cellHistograms(cellCountY, vector<vector<float>>(cellCountX, vector<float>(bin_size, 0)));
        for (int y = 0; y < cellCountY; y++) {
            for (int x = 0; x < cellCountX; x++) {
                for (int dy = 0; dy < cell_size; dy++) {
                    for (int dx = 0; dx < cell_size; dx++) {
                        int pixelY = y * cell_size + dy;
                        int pixelX = x * cell_size + dx;
                        float mag = magnitude.at<float>(pixelY, pixelX);
                        float ang = angle.at<float>(pixelY, pixelX);
                        int bin = cvRound(ang / 180.0 * bin_size) % bin_size;
                        cellHistograms[y][x][bin] += mag;
                    }
                }
            }
        }

        // Normalize histograms for each block
        int descriptorIndex = 0;
        for (int y = 0; y < blockCountY; y++) {
            for (int x = 0; x < blockCountX; x++) {
                vector<float> blockHistogram(block_size * block_size * bin_size, 0);
                for (int dy = 0; dy < block_size; dy++) {
                    for (int dx = 0; dx < block_size; dx++) {
                        int cellY = y + dy;
                        int cellX = x + dx;
                        for (int bin = 0; bin < bin_size; bin++) {
                            blockHistogram[dy * block_size * bin_size + dx * bin_size + bin] =
                                cellHistograms[cellY][cellX][bin];
                        }
                    }
                }
                float normFactor = 0;
                for (float val : blockHistogram) {
                    normFactor += val * val;
                }
                normFactor = sqrt(normFactor + 1e-6);
                for (float& val : blockHistogram) {
                    val /= normFactor;
                }
                for (float val : blockHistogram) {
                    hog_descriptor[descriptorIndex++] = val;
                }
            }
        }
    }


private:
    int cell_size;
    int block_size;
    int bin_size;
};

int main()
{
    Mat img = imread("musk.jpg");
    HOG hog = HOG();
    vector<float> hogDescriptor;
    hog.HOG_descriptor(img, hogDescriptor);

    cout << "HOG descriptor size: " << hogDescriptor.size() << endl;
    return 0;
}
