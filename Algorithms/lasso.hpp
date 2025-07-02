#include "algo.hpp"

class lasso : algo {
    public:
    int values;
    int features;
    Eigen::MatrixXf X;
    double lambda;
    Eigen::VectorXf beta;
    lasso(int values, int features, Eigen::MatrixXf X, double lambda);
    void fit();
    vector<double> predict();
    void testTrainSplit();
    private:
    Eigen::VectorXf coord_descent();
};