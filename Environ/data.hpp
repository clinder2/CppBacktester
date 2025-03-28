#ifndef DATA_H
#define DATA_H

#include <string>
#include </Users/christopherlinder/Desktop/CppBacktester/Environ/event.hpp>
//#include </Users/christopherlinder/Desktop/CppBacktester/Environ/event.cpp>

using namespace std;


class dataHandler {
    virtual vector<int> get_latest_bars(string symbol, int n)=0;
    virtual void update_bars()=0;
};



class historicDataHandler : dataHandler {
    historicDataHandler(vector<event> events, long start, long end, vector<string> symbol_list);
    private: 
        void _pull_process_symbols();
        vector<double> _get_new_bar(string symbol);  
};


#endif