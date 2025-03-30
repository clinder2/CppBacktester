#include </Users/christopherlinder/Desktop/CppBacktester/Environ/event.hpp>
#include </Users/christopherlinder/Desktop/CppBacktester/Environ/data.hpp>
#include <vector>

using namespace std;

historicDataHandler::historicDataHandler(vector<event>* _events, long _start, long _end, vector<string>* _symbol_list) {
    events = _events;
    start=_start;
    end=_end;
    symbol_list=_symbol_list;
}

vector<int> historicDataHandler::get_latest_bars(string symbol, int n) {
    vector<int> a;
    return a;
}