#include "lasso.hpp"

lasso::lasso(int _values, int _features, Eigen::MatrixXf _X, double _lambda) {
    values=_values;
    features=_features;
    X=_X;
    lambda=_lambda;
    beta=coord_descent();
}

void lasso::fit() {

}

vector<double> lasso::predict() {
    
}

void lasso::testTrainSplit() {

}

Eigen::VectorXf lasso::coord_descent() {
    double alpha = .1;
    //vector<double> beta(features, 1);
    features=10;
    values=10;
    X.resize(10,10);
    Eigen::VectorXf beta(features);
    Eigen::VectorXf labels(values);
    for (int i = 0; i<=1; i++) {
        for (int j = 0; j < features; j++) {
            beta(j)+=alpha;
            Eigen::VectorXf x(features);
            x=X*beta;
            double a1 = (x-labels).norm()+lambda*beta.norm();
            beta(j)-=2*alpha;
            x=X*beta;
            double a2 = (x-labels).norm()+lambda*beta.norm();
            if (a2>a1) {
                beta(j)+=2*alpha;
            }
            cout<<beta<<" a\n";
        }
        cout<<X;
    }
    return beta;
}