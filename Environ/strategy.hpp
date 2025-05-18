#ifndef STRATEGY_H
#define STRATEGY_H

//#include "event.hpp"
//#include "data.hpp"
#include "eventDatautils.hpp"

using namespace std;

// base strategy class-init to buy and hold
class strategy_base {
    public:
        dataHandler* bars;
        vector<string> symbol_list;
        deque<event*>* events;
        map<string, bool> bought;
        strategy_base(dataHandler* _bars, deque<event*>& _events) {
            bars=_bars;
            symbol_list = *(_bars->symbol_list);
            events=&_events;
        }
        virtual void calculate_signals(event e)=0;
        virtual void plotData(int type)=0;
};

class strategy : public strategy_base {
    public:
        /* dataHandler* bars;
        vector<string> symbol_list;
        deque<event*>* events;
        map<string, bool> bought; */
        strategy(dataHandler* bars, deque<event*>& events);
        void calculate_signals(event e);
        void plotData(int type);

    private:
        map<string, bool> _calculate_initial_bought();
};

#endif