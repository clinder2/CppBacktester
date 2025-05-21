#ifndef GUTILS
#define GUTILS

#define WITHOUT_NUMPY
#include "../matplotlib-cpp/matplotlibcpp.h"
#include <vector>
#include <string>
#include "../data.hpp"

using namespace std;
namespace plt = matplotlibcpp;

void plotTimeSeries(vector<bar> ts, long time_step=1);
void plotTimeSeries(vector<double> ts, long time_step=1);
void BrollingerPlot(vector<double>& MA, vector<double>& low, vector<double>& high, long time_step);

#endif