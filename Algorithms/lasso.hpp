#include "algo.hpp"
#include <Eigen/Dense>

class lasso : algo {
    public:
    int values;
    int features;
    Eigen::MatrixXf X;
    double lambda;
    lasso(int values, int features, Eigen::MatrixXf X, double lambda);
    void fit();
    vector<double> predict();
    void testTrainSplit();
    private:
    vector<double> coord_descent();
};