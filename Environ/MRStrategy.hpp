#include "strategy.hpp"
#include "graphing/graphUtils.hpp"

class MRStrategy : public strategy_base {
    public:
        int window; //lookback window
        map<string, vector<double> > sum;
        map<string, vector<double> > upper;
        map<string, vector<double> > lower;
        MRStrategy(dataHandler* bars, deque<event*>& events, int _window);

        void calculate_signals(event e);

        void plotData(int type);

        void plotBrollinger(string symbol);

    private:
        void updateSMA();
};