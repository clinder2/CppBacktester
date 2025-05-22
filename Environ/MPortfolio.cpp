//#include "event.hpp"
//#include "portfolio.hpp"
#include "MPortfolio.hpp"
#include "event.hpp"

MPortfolio::MPortfolio(dataHandler* _bars, deque<event*>& _events, long _start_date, long _init_capital) : naivePortfolio( _bars, _events, _start_date, _init_capital) {};

orderEvent* MPortfolio::generate_order(signalEvent signal) {
    string symbol = signal.symbol;
    string algo = signal.algo;

    long order_quantity = signal.quantity;
    double curr_quantity = current_positions[symbol];
    string order_type = "MKT";
    int quantity = 0;
    string direction = signal.signal_type;

    if (algo=="MR") {
        if (signal.meta=="LMT") {
            cout<<"gen LMT\n";
            return generate_LMT_order(signal);
        }
        if (direction=="SELL" && curr_quantity>=order_quantity) {
            quantity = order_quantity;
        } else if (direction=="BUY") {
            quantity=order_quantity;
        } else {
            quantity=0;
        }
    }

    orderEvent* order = new orderEvent(symbol, order_type, quantity, direction);
    order->setPort(id);
    return order;
}

orderEvent* MPortfolio::generate_LMT_order(signalEvent signal) {
    orderEvent* e = new orderEvent(signal.symbol, "LMT", signal.quantity, signal.signal_type);
    e->setPort(id);
    return e;
}

void MPortfolio::update_signal(signalEvent signal) {
    if (signal.type=="SIGNAL") {
        orderEvent* order = generate_order(signal);
        events->push_back(order);
    }
}