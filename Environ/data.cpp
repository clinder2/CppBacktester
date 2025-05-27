#include "event.hpp"
#include "data.hpp"
#include <vector>
#include <map>

using namespace std;

/* historicDataHandler::historicDataHandler(vector<event>* _events, long _start, long _end, vector<string>* _symbol_list, string path) : dataHandler() {
    events = _events;
    start=_start;
    end=_end;
    symbol_list=_symbol_list;
    historic_csv_path = path;

    bool continue_backtest;

    _pull_process_symbols();
} */

dataHandler::dataHandler() {
    
}

historicDataHandler::historicDataHandler() {

}

vector<bar> historicDataHandler::get_latest_bars(string symbol, int n) {
    vector<bar>* bars = latest_symbol_data[symbol];
    vector<bar> latest;
    if (bars->size()>=n) {
        while (n>0) {
            latest.push_back(bars->at(bars->size()-n));
            n--;
        }
    }
    return latest;
}

void historicDataHandler::update_bars() {
    for (auto s : *symbol_list) {
        bar curr = _get_new_bar(s);
        if (curr.time!=-1) {
            latest_symbol_data[s]->push_back(curr);
        }
    }
    marketEvent* m = new marketEvent();
    events->push_back(m);
    //pthread_cond_signal(&data_var);
}