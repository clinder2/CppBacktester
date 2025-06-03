#define _USE_MATH_DEFINES
#include "LogReg.hpp"

LogReg::LogReg(vector<bar> data, int _numLags, bool _useVol) : algo(data) {
    numLags = _numLags;
    useVol=_useVol;
    tt_ratio = .5;
    vector<double> thetas(numLags+1, 1); //thetas in ascending order
    testTrainSplit();
    makedata();
}

double LogReg::LL(int i) {
    double e = thetas[0];
    for (int j = 1; j <= numLags; j++) {
        e+=thetas[j]*pct_change[i-(numLags-j)];
    }
    return pow(M_E, e)/(1+pow(M_E, e));
}

void LogReg::fit() {
    for (int i = 0; i < 100; i++) {
        vector<double> v(pct_change.size()-numLags+1);
        int j = numLags-1;
        generate_n(v.begin(), v.end(), [&j]() {
            return LL(j++);
        });
        vector<double> dt(v.size());
        j=0;
        generate_n(dt.begin(), dt.end(), [&j]() {
            return (v[j]-LH[j])*pct_change[j];
        });
        j=0;
        generate_n(thetas.begin(), thetas.end(), [&j]() {
            return thetas[j] + dt[j];
        });
    }
}

void LogReg::testTrainSplit() {
    
}

vector<int> LogReg::getLH() {
    for (int i = 0; i < pct_change.size(); i++) {
        LH.push_back(signbit(pct_change[i]));
    }
}

void LogReg::makedata() {
    for (int i = 1; i < data.size(); i++) {
        pct_change.push_back((data[i].close-data[i-1].close)/data[i-1].close);
    }
}