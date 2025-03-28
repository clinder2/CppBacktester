#ifndef EVENT_H
#define EVENT_H

#include <string>

using namespace std;


class event {
    
};

class marketEvent : event {
    public:
        string type;
        marketEvent();
};

class signalEvent : event {
    public:
        string type;
        string symbol;
        long datetime;
        string signal_type;
        signalEvent(string _symbol, long _datetime, string _signal_type);
};

class orderEvent : event {
    string type;
    string symbol;
    string order_type;
    int quantity;
    int direction;
    orderEvent(string _symbol, string order_type, int quantity, int direction);
};

class fillEvent : event {
    string type;
    long date_time;
    string symbol;
    string exchange;
    int quantity;
    int direction;
    float fill_cost;
    float commission;
    fillEvent(string _symbol, float _date_time, string _exchange, 
        int quantity, int direction, float _fill_cost, float _commission);
    float calculate_ib_commission(float commission);
};


#endif