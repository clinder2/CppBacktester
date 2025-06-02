#include "TSAStrategy.hpp"

TSAStrategy::TSAStrategy(dataHandler* _bars, deque<event*>& _events) : strategy_base(_bars, _events) {

}

void TSAStrategy::calculate_signals(event e) {
    if (e.type=="MARKET") {
        long datetime = bars->latest_symbol_data[symbol_list[0]]->back().time;
        for (auto s : symbol_list) {
            vector<bar> latest = bars->get_latest_bars(s, n);
            if (latest.size()>=n) {
                vector<double> coeffs = DB(latest, n);
                double next=0;
                for (int i = n-1; i>=0; i--) {
                    next+=coeffs[i]*latest[latest.size()-n+i].close;
                    //cout<<s<<", "<<coeffs[i]<<", "<<next<<", "<<latest[latest.size()-n+i].close<<" c\n";
                }
                cout<<next<<" next\n";
                if (bars->latest_symbol_data[s]->back().close > next) {
                    signalEvent* signal = new signalEvent(s, datetime, "SELL", 1, "TSA");
                    events->push_back(signal);
                } else {
                    signalEvent* signal = new signalEvent(s, datetime, "BUY", 1, "TSA");
                    events->push_back(signal);
                }
            }
        }
    }
}

void TSAStrategy::plotData(int type) {

}