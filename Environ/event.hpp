#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <stdexcept>
#include <vector>
#include <deque>

using namespace std;


class event {
    public:
        string type;
        virtual ~event() {};
};


class marketEvent : public event {
    public:
        marketEvent() {
            type = "MARKET";
        }
};

class signalEvent : public event {
    public:
        string symbol;
        long datetime;
        string signal_type;
        long quantity;
        string algo;
        signalEvent(string _symbol, long _datetime, string _signal_type, long _quantity, string _algo) {
            type = "SIGNAL";
            symbol=_symbol;
            datetime=_datetime;
            signal_type=_signal_type;
            quantity=_quantity;
            algo=_algo;
        }
};

class complexSignalEvent : public signalEvent {
    public:
        long quantity;
        string algo;
        complexSignalEvent(string symbol, long datetime, long _quantity, string signal_type, string _algo) : signalEvent(symbol ,datetime, signal_type, _quantity, _algo) {
            type="COMPLEX";
            quantity = _quantity;
            algo=_algo;
        }
};

class orderEvent : public event {
    public:
        string symbol;
        string order_type;
        int quantity;
        string direction;
        long auxPrice;

        orderEvent() {
            type="ORDER";
        }

        orderEvent(string _symbol, string _order_type, int _quantity, string _direction) {
            type = "ORDER";
            symbol=_symbol;
            order_type=_order_type;
            quantity=_quantity;
            direction=_direction;
        }

        void setAuxPrice(long a) {
            auxPrice = a;
        }
};

class fillEvent : public event {
    public:
        //string type;
        long date_time;
        string symbol;
        string exchange;
        int quantity;
        string direction;
        float fill_cost;
        float commission;
        fillEvent(string _symbol, float _date_time, string _exchange, int _quantity, string _direction, float _fill_cost, float _commission) {
            type = "FILL";
            symbol=_symbol;
            date_time=_date_time;
            exchange=_exchange;
            quantity=_quantity;
            direction=_direction;
            fill_cost=_fill_cost;
            commission=calculate_ib_commission(commission);
        }
        float calculate_ib_commission(float commission);
};


#endif