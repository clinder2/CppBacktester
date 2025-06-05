#define _USE_MATH_DEFINES
#include "LogReg.hpp"

algo::algo() {}

algo::algo(vector<bar> _data) {data = _data;}

LogReg::LogReg(vector<bar> data, int _numLags, bool _useVol) : algo(data) {
    numLags = _numLags;
    useVol=_useVol;
    tt_ratio = .5;
    vector<double> thetas(numLags+1, 1); //thetas in ascending order
    testTrainSplit();
    makedata();
    getLH();
}

double LogReg::LL(int i) {
    double e = thetas[0];
    cout<<i<<"\n";
    for (int j = 1; j <= numLags; j++) {
        cout<<i-(numLags-j)<<"\n";
        e+=thetas[j]*pct_change[i-(numLags-j)];
    }
    return pow(M_E, e)/(1+pow(M_E, e));
}

void LogReg::fit() {
    for (int i = 0; i < 1; i++) {
        vector<double> v(pct_change.size()-numLags+1);
        int off = numLags-1;
        for (int k = 0; k < v.size(); k++) {
            cout<<k+off;
            v[k] = LL(k+off);
        }
        /* vector<vector<double> > dt(thetas.size(), *(new vector<double>));
        for (int j = 0; j < v.size(); j++) {
            dt[0].push_back((v[j]-LH[j+off]));
        }
        for (int k = 1; k < thetas.size(); k++) {
            for (int j = 0; j < v.size(); j++) {
                dt[k].push_back((v[j]-LH[j+off])*pct_change[j+off-(k-1)]);
            }
        } */
    }
}

vector<double> LogReg::predict() {

}

void LogReg::testTrainSplit() {
    
}

void LogReg::getLH() {
    vector<int> LH(pct_change.size());
    for (int i = 0; i < pct_change.size(); i++) {
        LH.push_back(signbit(pct_change[i]));
    }
}

void LogReg::makedata() {
    for (int i = 1; i < data.size(); i++) {
        pct_change.push_back((data[i].close-data[i-1].close)/data[i-1].close);
    }
}