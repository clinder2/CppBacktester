#include "portfolio.hpp"
//#include "event.hpp"
#include <algorithm>

class naivePortfolio : public portfolio {
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
        naivePortfolio(dataHandler* _bars, deque<event*>& _events, long _start_date, long _init_capital=1000) {
            bars=_bars;
            symbol_list=bars->symbol_list;
            events=&_events;
            start_date=_start_date;
            init_capital=_init_capital;

            for (auto s : *symbol_list) {
                current_positions[s] = 0.0;
            }
            all_positions=construct_all_positions();
            all_holdings=construct_all_holdings();
            current_holdings=construct_current_holdings();
        }

        vector<map<string, double> > construct_all_positions() {
            map<string, double> d = *(new map<string,double>());
            for (auto s : *symbol_list) {
                d[s] = 0.0;
            }
            d["datetime"] = start_date;
            vector<map<string, double> > p;
            p.push_back(d);
            return p;
        }

        vector<map<string, double> > construct_all_holdings() {
            map<string, double> d = *(new map<string,double>());
            d["datetime"] = start_date;
            d["cash"] = init_capital;
            d["commission"] = 0.0;
            d["total"] = init_capital;
            vector<map<string, double> > p;
            p.push_back(d);
            return p;
        }

        map<string, double> construct_current_holdings() {
            map<string, double> d = *(new map<string,double>());
            d["cash"] = init_capital;
            d["commission"] = 0.0;
            d["total"] = init_capital;
            return d;
        }

        void update_timeindex(event e) {
            map<string, bar> b;
            for (auto s : *symbol_list) {
                b[s] = bars->get_latest_bars(s).back();
            }
            map<string, double> d = *(new map<string,double>());
            string name = symbol_list->at(0);
            d["datetime"] = b[name].time;
            for (auto s : *symbol_list) {
                d[s] = current_positions[s];
            }
            all_positions.push_back(d);

            map<string, double> dh;
            dh["datetime"] = b[name].time;
            dh["cash"] = current_holdings["cash"];
            dh["commission"] = current_holdings["commission"];
            dh["total"] = current_holdings["cash"];

            for (auto s : *symbol_list) {
                double market_value = current_positions[s] * b[s].close;
                dh[s] = market_value;
                dh["total"]+=market_value;
            }

            all_holdings.push_back(dh);
            current_holdings=dh; //update current holdings with timeindex
        }

        void update_positions_from_fill(fillEvent fill) {
            int fill_d = 0;
            if (fill.direction=="BUY") {
                fill_d=1;
            } else if (fill.direction=="SELL") {
                fill_d=-1;
            }
            current_positions[fill.symbol]+=(fill_d*fill.quantity);
        }

        void update_holdings_from_fill(fillEvent fill) {
            int fill_d = 0;
            if (fill.direction=="BUY") {
                fill_d=1;
            } else if (fill.direction=="SELL") {
                fill_d=-1;
            }
            double fill_cost = bars->get_latest_bars(fill.symbol).at(0).close;
            double cost = fill_d*fill_cost*fill.quantity;
            current_holdings[fill.symbol]+=cost;
            current_holdings["commission"]+=fill.commission;
            current_holdings["cash"]-=(cost+fill.commission);
            current_holdings["total"]-=(cost+fill.commission);
        }

        void update_signal(signalEvent signal) {
            if (signal.type=="SIGNAL") {
                orderEvent* order = generate_naive_order(signal);
                events->push_back(order);
            }
        }
        void update_fill(fillEvent e) {
            if (e.type=="FILL") {
                update_positions_from_fill(e);
                update_holdings_from_fill(e);
            }
        }

        orderEvent* generate_naive_order(signalEvent signal) {
            string symbol = signal.symbol;
            string direction = signal.signal_type;
            int strength = 1; //fix

            int mkt_quantity = floor(100*strength);
            double curr_quantity = current_positions[symbol];
            string order_type = "MKT";

            long quantity=mkt_quantity;
            string order_direction = "";

            if (direction=="LONG" && curr_quantity==0) {
                order_direction="BUY";
            } else if (direction=="SHORT" && curr_quantity>0) {
                order_direction="SELL";
            }
            if (direction=="EXIT" && curr_quantity>0) {
                quantity=abs(curr_quantity);
                order_direction="SELL";
            }
            if (direction=="EXIT" && curr_quantity<0) {
                quantity=abs(curr_quantity);
                order_direction="BUY";
            }
            
            orderEvent* order = new orderEvent(symbol, order_type, mkt_quantity, order_direction);
            return order;
        }
};

/* int main() {
    deque<event>* queue = new deque<event>();
    vector<string> sym;
    sym.push_back("AAPL");
    sym.push_back("IONQ");
    sym.push_back("NVDA");
    historicDataHandler* h = new historicDataHandler(queue, 0, 0, &sym, "/Users/christopherlinder/Desktop/CppBacktester/HistoricData/test.csv");
    h->update_bars();
    //cout<<h->symbol_data["AAPL"].size()<<" a \n";
    naivePortfolio* p = new naivePortfolio(h, queue, 0);
} */