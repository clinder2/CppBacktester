#include "signature.hpp"

vector<double> lead_t(vector<bar> d) {
    vector<double> tr(2*d.size());
    tr[0]=d[0].close;
    for (int i = 1; i < d.size(); i++) {
        tr[2*i-1]=d[i].close;
        tr[2*i]=d[i].close;
    }
    return tr;
}

vector<double> lag_t(vector<bar> d) {
    vector<double> tr(2*d.size());
    for (int i = 0; i < d.size(); i++) {
        tr[2*i]=d[i].close;
        tr[2*i+1]=d[i].close;
    }
    return tr;
}

void plotLeadLag(vector<bar> data) {
    vector<double> lead = lead_t(data);
    vector<double> lag = lag_t(data);
    plt::plot(lead, lag);
    plt::show();
}

Eigen::MatrixXf sig_matrix(vector<vector<double> > datastreams) {
    
}