#ifndef STRATEGY_H
#define STRATEGY_H

#include "event.hpp"
#include "data.hpp"
#include "data.cpp"

using namespace std;

// base strategy class-init to buy and hold
class strategy {
    public:
        dataHandler* bars;
        vector<string> symbol_list;
        vector<event>* events;
        map<string, bool> bought;
        strategy(dataHandler* bars, vector<event>* events);
        void calculate_signals(event e);

    private:
        map<string, bool> _calculate_initial_bought();
};

#endif