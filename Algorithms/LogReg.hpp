#include "algo.hpp"

class LogReg : algo {
    public:
        int numLags;
        bool useVol;
        double tt_ratio;
        vector<int> LH;
        LogReg(vector<bar> data, int numLags, bool useVol);
        void fit();
        vector<double> predict();
        void testTrainSplit();
    
    private:
        vector<double> pct_change;
        vector<double> thetas; //thetas in ascending order
        void getLH();
        void makedata();
        double LL(int i);
};