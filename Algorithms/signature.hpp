#include "algo.hpp"

vector<double> lead_t(vector<bar> d);
vector<double> lag_t(vector<bar> d);
void plotLeadLag(vector<bar> data);

Eigen::MatrixXf sig_matrix(vector<vector<double> > datastreams);