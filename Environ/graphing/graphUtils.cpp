#include "graphUtils.hpp"

void plotTimeSeries(vector<bar> ts, long time_step) {
    vector<double> time(ts.size());
    generate(time.begin(), time.end(), [n=0, &time_step]() mutable {return n+=time_step;});
    vector<double> close;
    for (auto b : ts) {
        close.push_back(b.close);
    }
    plt::plot(time, close);
    plt::show();
}

void plotTimeSeries(vector<double> ts, long time_step) {
    vector<double> time(ts.size());
    generate(time.begin(), time.end(), [n=0, &time_step]() mutable {return n+=time_step;});
    cout<<"plot\n";
    plt::plot(time, ts);
    plt::show();
}

void BrollingerPlot(vector<double> &MA, vector<double> &low, vector<double> &high, long time_step) {
    vector<double> time(MA.size());
    generate(time.begin(), time.end(), [n=0, &time_step]() mutable {return n+=time_step;});
    plt::plot(time, MA);
    plt::plot(time, low);
    plt::plot(time, high);
    plt::show();
}