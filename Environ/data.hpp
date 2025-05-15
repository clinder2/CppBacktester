#ifndef DATA_H
#define DATA_H

#include <new>
#include <string>
#include <map>
#include </Users/christopherlinder/Desktop/CppBacktester/Environ/event.hpp>
#include </Users/christopherlinder/Desktop/CppBacktester/Environ/reader.hpp>
//#include </Users/christopherlinder/Desktop/CppBacktester/Environ/event.cpp>

using namespace std;

struct bar {
    long time;
    double close;
    double high;
    double low;
    double open;
    double volume;
};

class dataHandler {
    public:
        virtual ~dataHandler() {};
        vector<string>* symbol_list;
        map<string, vector<bar>* > latest_symbol_data;
        dataHandler(vector<string>* _symbol_list) {
            symbol_list=_symbol_list;
        }
        virtual vector<bar> get_latest_bars(string symbol, int n=1) {};
        virtual void update_bars() {};
};

class historicDataHandler : public dataHandler {
    public: 
        ~historicDataHandler() {};
        deque<event*>* events;
        long start;
        long end;
        //vector<string>* symbol_list;
        map<string, map<long, map<string, double> > > symbol_data;
        //map<string, vector<bar>* > latest_symbol_data;
        string historic_csv_path;
        bool continue_backtest;

        map<string,int> symbol_index;
        vector<long> times;
        historicDataHandler(deque<event*>& _events, long _start, long _end, vector<string>* _symbol_list, string path) : dataHandler(_symbol_list) {
            events = &_events;
            start=_start;
            end=_end;
            symbol_list=_symbol_list;
            historic_csv_path = path;

            continue_backtest = true;

            _pull_process_symbols();
        }
        vector<bar> get_latest_bars(string symbol, int n=1) override;
        void update_bars() override;

    private:
        reader r;
        void _pull_process_symbols() {
            symbol_data = r._pull_process_symbols_from_csv(historic_csv_path, symbol_list);
            for (auto s : *symbol_list) {
                symbol_index[s] = 0;
                latest_symbol_data[s] = new vector<bar>();
            }
            map<long, map<string, double> > temp = symbol_data[(*symbol_list)[0]];
            for (auto p : temp) {
                times.push_back(p.first);
            }
        }
        bar _get_new_bar(string symbol) {
            if (symbol_index[symbol]<times.size()) {
                map<long, map<string, double> > data = symbol_data[symbol];
                long t = times[symbol_index[symbol]];
                symbol_index[symbol]++;
                bar temp;
                temp.time = t;
                temp.close = data[t]["Close"];
                temp.high = data[t]["High"];
                temp.low = data[t]["Low"];
                temp.open = data[t]["Open"];
                temp.volume = data[t]["Volume"];
                return temp;
            } else {
                continue_backtest=false;
                bar temp;
                temp.time = -1;
                return temp;
            }
        }
};


#endif