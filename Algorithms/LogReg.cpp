#include <numeric>
#define _USE_MATH_DEFINES
#include "LogReg.hpp"

algo::algo() {}

algo::algo(vector<bar> _data) {data = _data;}

LogReg::LogReg(vector<bar> data, int _numLags, bool _useVol) : algo(data) {
    numLags = _numLags;
    useVol=_useVol;
    tt_ratio = .5;
    thetas = *(new vector<double>(numLags+1, 1)); //thetas in ascending order
    testTrainSplit();
    makedata();
    getLH();
}

double LogReg::LL(int i) {
    double e = thetas[0];
    for (int j = 1; j <= numLags; j++) {
        e+=thetas[j]*pct_change[i-(numLags-j)];
        //cout<<thetas[j]<<", "<<pct_change[i-(numLags-j)]<<"\n";
    }
    //cout<<e<<", "<<pow(M_E, e)<<"\n";
    return pow(M_E, e)/(1+pow(M_E, e));
}

void LogReg::fit() {
    for (int i = 0; i < 3; i++) {
        vector<double> v(pct_change.size()-numLags+1);
        int off = numLags-1;
        for (int k = 0; k < v.size(); k++) {
            v[k] = LL(k+off);
        }
        vector<vector<double> > dt(thetas.size(), *(new vector<double>()));
        for (int j = 0; j < v.size(); j++) {
            dt[0].push_back((v[j]-LH[j+off]));
            //cout<<dt[0].back()<<", "<<v[j]<<", "<<LH[j+off]<<", "<<j+off<<"\n";
        }
        for (int k = 1; k < thetas.size(); k++) {
            for (int j = 0; j < v.size(); j++) {
                dt[k].push_back((v[j]-LH[j+off])*pct_change[j+off-(k-1)]);
            }
            //cout<<dt[k][0]<<" dt\n";
        }
        for (int j = 0; j < thetas.size(); j++) {
            double s = 0;
            for (auto v : dt[j]) {
                s+=v;
                //cout<<v<<"\n";
            }
            //cout<<dt[j][0]<<", "<<accumulate(dt[j].begin(), dt[j].end(), 0)<<"\n";
            thetas[j] += .5*s;
        }
        for (auto i : thetas) {
            cout<<i<<" theta\n";
        }
    }
    cout<<LL(3);
}

vector<double> LogReg::predict() {

}

void LogReg::testTrainSplit() {
    
}

void LogReg::getLH() {
    LH = *(new vector<int>());
    for (int i = 0; i < pct_change.size(); i++) {
        LH.push_back(signbit(pct_change[i]));
    }
}

void LogReg::makedata() {
    for (int i = 1; i < data.size(); i++) {
        pct_change.push_back((data[i].close-data[i-1].close)/data[i-1].close);
    }
}