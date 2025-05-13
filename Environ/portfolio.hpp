#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "event.hpp"
#include "data.hpp"
#include "data.cpp"

class portfolio {
    public:
        dataHandler* bars;
        vector<string>* symbol_list;
        deque<event*>* events;
        long start_date;
        long init_capital;

        vector<map<string, double> > all_positions;
        map<string, double> current_positions;
        vector<map<string, double> > all_holdings;
        map<string, double> current_holdings;

        virtual ~portfolio() {};
        virtual void update_timeindex(event e) {};
        virtual void update_signal(signalEvent e) {};
        virtual void update_fill(fillEvent e) {};
};

#endif