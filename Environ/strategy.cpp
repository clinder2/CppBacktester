#include "strategy.hpp"

strategy::strategy(dataHandler* _bars, deque<event*>& _events) : strategy_base(_bars, _events) {
    //bars = _bars;
    //symbol_list = *(_bars->symbol_list);
    //events = &_events;

    bought = _calculate_initial_bought();
}

map<string, bool> strategy::_calculate_initial_bought() {
    map<string, bool> bought = *(new map<string, bool>);
    for (auto s : symbol_list) {
        bought[s] = false;
    }
    return bought;
}

void strategy::calculate_signals(event e) {
    if (e.type=="MARKET") {
        for (auto s : symbol_list) {
            vector<bar> b = bars->get_latest_bars(s,1);
            long datetime = b[0].time;
            if (b.size()>0) {
                if (!bought[s]) {
                    signalEvent* signal = new signalEvent(s, datetime, "LONG", 1, "BUYANDHOLD");
                    events->push_back(signal);
                    bought[s] = true;
                }
            }
        }
    }
}

void strategy::plotData(int type) {

}