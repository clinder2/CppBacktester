#include "eventDatautils.hpp"
#include "strategy.hpp"

//startegy class for testing basic TSA algos, Durbin-Levinson, Innovations, etc.
class TSAStrategy : public strategy_base {
    public:
        TSAStrategy();
        TSAStrategy(dataHandler* _bars, deque<event*>& _events);
        void calculate_signals(event e);
        void plotData(int type);
};