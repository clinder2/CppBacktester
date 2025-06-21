#include "lasso.hpp"

lasso::lasso(int _values, int _features, Eigen::MatrixXf _X, double _lambda) {
    values=_values;
    features=_features;
    X=_X;
    lambda=_lambda;
}

void lasso::fit() {

}

vector<double> lasso::predict() {
    
}

void lasso::testTrainSplit() {

}

vector<double> lasso::coord_descent() {
    double alpha = .1;
    vector<double> beta(features, 1);
    for (int i = 0; i<=10; i++) {
        for (int j = 0; j < features; j++) {
            
        }
    }
}