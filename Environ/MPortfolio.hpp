#include "portfolio.hpp"

class MPortfolio : public naivePortfolio {
    public:
        MPortfolio(dataHandler* _bars, deque<event*>& _events, long _start_date, long _init_capital=1000);
        
        orderEvent* generate_order(signalEvent signal);

        orderEvent* generate_LMT_order(signalEvent signal);

        void update_signal(signalEvent signal);
};