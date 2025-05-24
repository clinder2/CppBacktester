#include "sampleACF.hpp"
#include <numeric>

long sm(vector<bar> v) {
    int n = v.size();
    long x = accumulate(v.begin(), v.end(), 0, 
        [](int sum, const bar& b) {
            return sum+b.close;
        });
    return x/n;
}

long s_autocovf(vector<bar> v, int h) {
    int n = v.size();
    long x_ = sm(v);
    int gamma;
    h=abs(h);
    for (int i = 0; i < n-h; i++) {
        gamma+=(v[i+h].close-x_)*(v[i].close-x_);
    }
    return gamma/n;
}

long sample_acf(vector<bar> v, int h) {
    return s_autocovf(v, h)/s_autocovf(v,0);
}