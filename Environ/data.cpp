#include </Users/christopherlinder/Desktop/CppBacktester/Environ/event.hpp>
#include </Users/christopherlinder/Desktop/CppBacktester/Environ/data.hpp>
#include <vector>
#include <map>

using namespace std;

historicDataHandler::historicDataHandler(vector<event>* _events, long _start, long _end, vector<string>* _symbol_list, string path) {
    events = _events;
    start=_start;
    end=_end;
    symbol_list=_symbol_list;
    historic_csv_path = path;

    //map<string, map<string, double> > symbol_data;
    //map<string, map<long, map<string, double> > > = latest_symbol_data;
    bool continue_backtest;

    _pull_process_symbols();
}

vector<int> historicDataHandler::get_latest_bars(string symbol, int n) {
    vector<int> a;
    return a;
}

void historicDataHandler::update_bars() {

}

int main() {
    vector<event>* queue;
    vector<string> sym;
    sym.push_back("AAPL");
    sym.push_back("IONQ");
    sym.push_back("NVDA");
    historicDataHandler h(queue, 0, 0, &sym, "/Users/christopherlinder/Desktop/CppBacktester/HistoricData/test.csv");
}