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
    virtual vector<bar> get_latest_bars(string symbol, int n=1)=0;
    virtual void update_bars()=0;
};


class historicDataHandler : dataHandler {
    public: 
        vector<event>* events;
        long start;
        long end;
        vector<string>* symbol_list;
        map<string, map<long, map<string, double> > > symbol_data;
        map<string, vector<bar>* > latest_symbol_data;
        string historic_csv_path;

        map<string,int> symbol_index;
        vector<long> times;
        historicDataHandler(vector<event>* events, long start, long end, vector<string>* symbol_list, string path);
        vector<bar> get_latest_bars(string symbol, int n=1);
        void update_bars();

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
                bar temp;
                temp.time = -1;
                return temp;
            }
        }
};


#endif