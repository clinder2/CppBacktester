#include </Users/christopherlinder/Desktop/CppBacktester/Environ/event.hpp>

using namespace std;
using namespace event;

marketEvent::marketEvent() {
    type = "MARKET";
}

signalEvent::signalEvent(string _symbol, long _datetime, string _signal_type) {
    type = "SIGNAL";
    symbol=_symbol;
    datetime=_datetime;
    signal_type=_signal_type;
}

orderEvent::orderEvent(string _symbol, string _order_type, int _quantity, int _direction) {
    type = "ORDER";
    symbol=_symbol;
    order_type=_order_type;
    quantity=_quantity;
    direction=_direction;
}

fillEvent::fillEvent(string _symbol, float _date_time, string _exchange, int _quantity, int _direction, float _fill_cost, float _commission) {
    type = "ORDER";
    symbol=_symbol;
    date_time=_date_time;
    exchange=_exchange;
    quantity=_quantity;
    direction=_direction;
    fill_cost=_fill_cost;
    commission=calculate_ib_commission(commission);
}

float fillEvent::calculate_ib_commission(float commission) {
    float full_cost=1.3;
    return full_cost*quantity*fill_cost;
}

int main() {
    //event* e = new event();
    return 0;
}