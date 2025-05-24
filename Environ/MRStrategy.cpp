//#include "strategy.hpp"
#include "MRStrategy.hpp"
//#include "/Users/christopherlinder/Desktop/CppBacktester/Environ/gnuplot-iostream/gnuplot-iostream.h"
//#include "/Users/christopherlinder/Library/Mobile Documents/.Trash/boost/boost/regex.hpp"

//mean reversion-Brollinger bands strategy
MRStrategy::MRStrategy(dataHandler* bars, deque<event*>& events, int _window) : strategy_base(bars, events) {
    window = _window;
    for (auto s : symbol_list) {
        sum[s] = *(new vector<double>());
        upper[s] = *(new vector<double>());
        lower[s] = *(new vector<double>());
    }
}

void MRStrategy::calculate_signals(event e) {
    if (e.type=="MARKET") {
        updateSMA();
        long datetime = bars->latest_symbol_data[symbol_list[0]]->back().time;
        for (string s : symbol_list) {
            string type="SELL";
            long quantity=1;
            double cost = bars->latest_symbol_data[s]->back().close;
            if (cost >= upper[s].back()) {
                type = "SELL";
            } else if (cost <= lower[s].back()) {
                type="BUY";
            }
            signalEvent* signal = new signalEvent(s, datetime, type, quantity, "MR");
            events->push_back(signal);

            if (cost>1.1*sum[s].back()/window) {
                long auxPrice = 1.1*sum[s].back()/window;
                quantity = (int)(.1*sum[s].back()/window);
                cout<<quantity<<" quantity\n";
                signalEvent* limit = new signalEvent(s, datetime, "BUY", quantity, "MR");
                limit->setMeta("LMT");
                limit->setAuxPrice(auxPrice);
                events->push_back(limit);
            }
            //cout<<upper[s].back()<<", "<<lower[s].back()<<", "<<cost<<"\n";
        }
    }
}

void MRStrategy::plotData(int type) {
    if (type==1) {
        string symbol = symbol_list.back();
        plotTimeSeries(sum[symbol], 1);
    } else if (type==2) {
        for (auto s : symbol_list) {
            plotBrollinger(s);
        }
    }
}

void MRStrategy::plotBrollinger(string symbol) {
    vector<double> MA;
    for (int i = 0; i < sum[symbol].size(); i++) {
        MA.push_back(sum[symbol][i]/window);
    }
    vector<double> low = lower[symbol];
    vector<double> high = upper[symbol];
    BrollingerPlot(MA, low, high, 1);
}

void MRStrategy::updateSMA() {
    map<string, vector<bar>* > data = bars->latest_symbol_data;
    for (auto s : symbol_list) {
        int n = data[s]->size();
        double value = data[s]->back().close;
        double next = value;
        if (data[s]->size() >= window) {
            next = sum[s].back() + value - data[s]->at(n-window).close;
        } else if (sum[s].size()>0) {
            next = sum[s].back()+value;
        }
        sum[s].push_back(next);
        double m = sum[s].back()/window;
        double sd;
        for (int i = max(0, n-window); i<n; i++) {
            sd+=pow(data[s]->at(i).close - m, 2);
        }
        sd=sqrt(sd/(window-1));
        upper[s].push_back(m+2*sd);
        lower[s].push_back(m-2*sd);
    }
}