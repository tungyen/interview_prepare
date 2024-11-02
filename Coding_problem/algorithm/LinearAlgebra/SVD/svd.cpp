#define _USE_MATH_DEFINES
#include <iostream>
#include <Eigen/Dense>
#include <cmath>
using namespace std;
using namespace Eigen;

class SVD{

public:

    SVD(){
        M = 3;
        R = 3;
        N = 3;
    }

    void doubleJacobi(MatrixXf A, MatrixXf *U, VectorXf *D, MatrixXf *V){
        M = static_cast<int>(A.rows());
        N = static_cast<int>(A.cols());
        R = min(M,N);
        MatrixXf ATA = A.transpose() * A;
        float error = 5e-4;


        // Compute the V vector by A.transpose() * A
        MatrixXf Q = MatrixXf::Identity(N, N);
        while(true){
            int p;
            int q;
            float mx = 0;
            for(int i = 0;i<N-1;i++){
                for(int j = i+1;j<N;j++){
                    if(abs(ATA(i,j))>mx){
                        mx = abs(ATA(i,j));
                        p = i;
                        q = j;
                    }
                }
            }
            if(mx < error){
                break;
            }
            else{
                float C;
                float S;
                if(ATA(p,p) == ATA(q,q)){
                    float theta = ATA(p, q) < 0 ? -M_PI / 4 : M_PI / 4;
                    C = cos(theta);
                    S = sin(theta);
                }
                else{
                    float c = (ATA(p,p)-ATA(q,q)) / (2 * ATA(p,q));
                    float T = c > 0 ? 1 / (abs(c)+sqrt(c*c+1)) : -1 / (abs(c)+sqrt(c*c+1));
                    C = 1 / sqrt(1 + T * T);
                    S = T * C;
                }
                MatrixXf Jacob = MatrixXf::Identity(N, N);
                Jacob(p,p) = C;
                Jacob(q,q) = C;
                Jacob(p,q) = -S;
                Jacob(q,p) = S;
                Q = Q * Jacob;
                ATA = Jacob.transpose() * ATA * Jacob;

            }
        }

        vector<float> eigenvalue;
        for(int i = 0;i<N;i++){
            if(fabs(ATA(i, i)) < error){
                continue;
            }
            else{
                eigenvalue.push_back(ATA(i,i));
            }
        }
        sort(eigenvalue.begin(), eigenvalue.end(), greater<float>());
        R = eigenvalue.size();
        *D = VectorXf(eigenvalue.size());
        for(int i = 0;i<eigenvalue.size();i++){
            (*D)[i] = sqrt(eigenvalue[i]);
        }
        *V = Q;
        *U = A * Q;
        for(int i = 0;i<eigenvalue.size();i++){
            VectorXf tmp = U->col(i) / eigenvalue[i];
            U->col(i) = tmp;
        }
    }

private:
    int M;
    int R;
    int N;
};

int main()
{
    SVD svd = SVD();
    MatrixXf A(3,3);
    A << 1, 2, 3,
        4, 5, 6,
        7, 8, 9;

    MatrixXf U;
    MatrixXf V;
    VectorXf D;
    svd.doubleJacobi(A, &U, &D, &V);
    cout<<"U: "<<U<<endl;
    cout<<"D: "<<D<<endl;
    cout<<"V: "<<V<<endl;
    MatrixXf sigma(3,3);
    sigma(0,0) = D[0];
    sigma(1,1) = D[1];
    //cout<<U * sigma * V.transpose()<<endl;
    return 0;
}
