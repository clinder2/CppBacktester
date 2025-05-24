#ifndef PORTFOLIO_H
#define PORTFOLIO_H

/* #include "event.hpp"
#include "data.hpp"
#include "data.cpp" */
#include "eventDatautils.hpp"
//#include "MRStrategy.cpp"

class portfolio {
    public:
        long id;
        dataHandler* bars;
        vector<string>* symbol_list;
        deque<event*>* events;
        long start_date;
        long init_capital;
        string strategy_type;
        string p_type;

        vector<map<string, double> > all_positions;
        map<string, double> current_positions;
        vector<map<string, double> > all_holdings;
        map<string, double> current_holdings;

        portfolio();
        virtual ~portfolio() {};
        virtual void update_timeindex(event e)=0;
        virtual void update_signal(signalEvent e)=0;
        virtual void update_fill(fillEvent e)=0;
        virtual void update_LMT_fill(orderEvent e)=0;
        void set_Strategy(string strategy) {
            strategy_type=strategy;
        }
        void set_ptype(string type) {
            p_type=type;
        }
};

class naivePortfolio : public portfolio {
    public:
        naivePortfolio(dataHandler* _bars, deque<event*>& _events, long _start_date, long _init_capital=1000);
        void update_timeindex(event e);
        void update_signal(signalEvent e);
        void update_fill(fillEvent e);
        vector<map<string, double> > construct_all_positions();
        vector<map<string, double> > construct_all_holdings();
        map<string, double> construct_current_holdings();
        void update_positions_from_fill(fillEvent fill);
        void update_holdings_from_fill(fillEvent fill);
        orderEvent* generate_naive_order(signalEvent signal);
        void update_LMT_fill(orderEvent e);
};

#endif