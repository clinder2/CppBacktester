#include "sampleACF.hpp"
#include <numeric>

double sm(vector<bar> v) {
    int n = v.size();
    double x=0;
    for (auto b : v) {
        x+=b.close;
    }
    return x/n;
}

double s_autocovf(vector<bar> v, int h) {
    int n = v.size();
    double x_ = sm(v);
    double gamma=0;
    h=abs(h);
    for (int i = 0; i < n-h; i++) {
        gamma+=(v[i+h].close-x_)*(v[i].close-x_);
        //cout<<x_<<", "<<v[i+h].close<<", "<<gamma<<" g\n";
    }
    return gamma/(n-1);
}

double sample_acf(vector<bar> v, int h) {
    return s_autocovf(v, h)/s_autocovf(v,0);
}