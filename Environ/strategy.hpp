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
        map<string, deque<orderEvent> > MITQ; //Queue for holding market if touched orders
        strategy_base(dataHandler* _bars, deque<event*>& _events) {
            bars=_bars;
            symbol_list = *(_bars->symbol_list);
            events=&_events;
            MITQ=*(new map<string, deque<orderEvent> >);
            for (auto s : symbol_list) {
                MITQ[s] = *(new deque<orderEvent>);
            }
        }
        virtual void calculate_signals(event e)=0;
        virtual void plotData(int type)=0;
        void updateMITQ(event e) {
            long datetime = bars->latest_symbol_data[symbol_list[0]]->back().time;
            for (auto s : symbol_list) {
                vector<bar> curr = bars->get_latest_bars(s);
                bar last_bar = curr.back();
                deque<orderEvent> Q = MITQ[s];
                int index=0;
                for (auto mit : Q) {
                    if (mit.order_type=="MIT") {
                        if (mit.direction=="BUY" && last_bar.close<=mit.auxPrice) {
                            signalEvent* signal = new signalEvent(s, datetime, "BUY", mit.quantity, "MR");
                            events->push_back(signal);
                            Q.erase(Q.begin()+index);
                        } else if (mit.direction=="SELL" && last_bar.close>=mit.auxPrice) {
                            signalEvent* signal = new signalEvent(s, datetime, "SELL", mit.quantity, "MR");
                            events->push_back(signal);
                            Q.erase(Q.begin()+index);
                        }
                        index++;
                    }
                }
            }
        }
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