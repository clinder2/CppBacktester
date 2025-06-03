#include "../Environ/eventDatautils.hpp"
#include <cmath>
#include <utility>

class algo {
    public:
        vector<bar> data;
        vector<bar> test;
        vector<bar> train;
        algo(vector<bar> data);
        virtual void fit();
        virtual vector<double> predict();
        virtual void testTrainSplit();
};