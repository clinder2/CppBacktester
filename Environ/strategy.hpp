#ifndef STRATEGY_H
#define STRATEGY_H

#include "event.hpp"
#include "data.hpp"

using namespace std;

// base strategy class-init to buy and hold
class strategy {
    public:
        dataHandler* bars;
        vector<string> symbol_list;
        deque<event*>* events;
        map<string, bool> bought;
        strategy(dataHandler* bars, deque<event*>& events);
        void calculate_signals(event e);

    private:
        map<string, bool> _calculate_initial_bought();
};

#endif