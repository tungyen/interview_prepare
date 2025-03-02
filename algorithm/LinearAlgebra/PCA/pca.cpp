#include <Eigen/Dense>
#include <iostream>
#include <vector>

using namespace std;
using namespace Eigen;

class PCA{

public:
    PCA(int k){
        K = k;
    }

    void ProjReconstruct(MatrixXf data){

        int d = data.cols();

        VectorXf mean = data.colwise().mean();
        MatrixXf diff = data.colwise() - mean;
        MatrixXf conv = diff.transpose() * diff;

        JacobiSVD<MatrixXf> svd(conv, ComputeFullU | ComputeFullV);
        MatrixXf U = svd.matrixU();

        // Get the eigenvectors with k largest eigenvalues
        MatrixXf ProjectionMatrix = U.block(0, 0, d, K);

        Projection = data * ProjectionMatrix;
        Reconstruction = Projection * ProjectionMatrix.transpose();
    }

    MatrixXf getProjection(){
        return Projection;
    }

    MatrixXf getReconstruction(){
        return Reconstruction;
    }

private:
    int K;
    MatrixXf Projection;
    MatrixXf Reconstruction;
};

int main()
{
    MatrixXf data = Eigen::MatrixXf::Random(100, 8);
    PCA pca = PCA(3);
    pca.ProjReconstruct(data);
    cout<<"row of Projection: "<<pca.getProjection().rows()<<", col of Projection: "<<pca.getProjection().cols()<<endl;
    cout<<"row of Reconstruction: "<<pca.getReconstruction().rows()<<", col of Reconstruction: "<<pca.getReconstruction().cols()<<endl;

    return 0;
}
