#include "../Environ/eventDatautils.hpp"
#include "../Environ/graphing/graphUtils.hpp"
#include <cmath>
#include <utility>
#ifndef ALGO
#define ALGO

class algo {
    public:
        vector<bar> data;
        vector<bar> test;
        vector<bar> train;
        algo();
        algo(vector<bar> data);
        virtual ~algo() {};
        virtual void fit()=0;
        virtual vector<double> predict()=0;
        virtual void testTrainSplit()=0;
};

#endif