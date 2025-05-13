#include "strategy.hpp"
#include "strategy.cpp"

//mean reversion-Brollinger bands strategy
class MRStrategy : public strategy {
    public:
        int window; //lookback window
        map<string, vector<double> > sum;
        map<string, vector<double> > sq_sum;
        map<string, vector<double> > upper;
        map<string, vector<double> > lower;
        MRStrategy(dataHandler* bars, deque<event*>& events, int _window) : strategy(bars, events) {
            window = _window;
            for (auto s : symbol_list) {
                sum[s] = *(new vector<double>());
                sq_sum[s] = *(new vector<double>());
                upper[s] = *(new vector<double>());
                lower[s] = *(new vector<double>());
            }
        }

        void calculate_signals(event e) {
            if (e.type=="MARKET") {
                updateSMA();
                long datetime = bars->latest_symbol_data[symbol_list[0]]->back().time;
                for (string s : symbol_list) {
                    string type="";
                    long quantity=1;
                    double cost = bars->latest_symbol_data[s]->back().close;
                    if (cost >= upper[s].back()) {
                        type = "SELL";
                    } else if (cost <= lower[s].back()) {
                        type="BUY";
                    }
                    complexSignalEvent* signal = new complexSignalEvent(s, datetime, quantity, type, "MR");
                    events->push_back(signal);
                }
            }
        }

    private:
        void updateSMA() {
            map<string, vector<bar>* > data = bars->latest_symbol_data;
            for (auto s : symbol_list) {
                int n = data[s]->size();
                double next = 0;
                double value = data[s]->back().close;
                if (data[s]->size()>=window) {
                    next = sum[s].back() + value - data[s]->at(n-window).close;
                    //next/=window;
                } else {
                    next = sum[s].back()+value;
                }
                sum[s].push_back(next);
                double prev=0;
                if (n>=1) {
                    prev = sq_sum[s].back()+(value*value);
                } else {
                    prev = value*value;
                }
                sq_sum[s].push_back(prev);
                double m = sum[s].back()/window;
                double sd = ((sq_sum[s].back()-sq_sum[s].at(max(0, n+1-window)))/window)-(m*m);
                upper[s].push_back(m+2*sd);
                lower[s].push_back(m-2*sd);
            }
        }
};