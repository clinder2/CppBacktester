//#include "event.hpp"
//#include "portfolio.hpp"
#include "portfolio.cpp"

class MPortfolio : public naivePortfolio {
    public:
        MPortfolio(dataHandler* _bars, deque<event*>& _events, long _start_date, long _init_capital=1000) : naivePortfolio( _bars, _events, _start_date, _init_capital) {};
        
        orderEvent* generate_order(signalEvent signal) {
            string symbol = signal.symbol;
            string algo = signal.algo;

            long order_quantity = signal.quantity;
            double curr_quantity = current_positions[symbol];
            string order_type = "MRK";
            int quantity = 0;
            string direction = signal.type;

            if (algo=="MR") {
                if (direction=="SELL" && curr_quantity>=order_quantity) {
                    quantity = order_quantity;
                } else if (direction=="BUY") {
                    quantity=order_quantity;
                } else {
                    quantity=0;
                }
            }

            orderEvent* order = new orderEvent(symbol, order_type, quantity, direction);
            return order;
        }

        void update_signal(signalEvent signal) {
            if (signal.type=="SIGNAL") {
                orderEvent* order = generate_order(signal);
                events->push_back(order);
            }
        }
};