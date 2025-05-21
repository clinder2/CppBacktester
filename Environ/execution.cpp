#include "execution.hpp"
#include <chrono>
#include <ctime>
#include <iostream>

/* simulatedExecutionHandler::simulatedExecutionHandler(deque<event*>& _events) {
    events=&_events;
    book=HM_LOB();
} */

void simulatedExecutionHandler::execute_order(orderEvent e) {
    if (e.type=="ORDER") {
        auto curr = chrono::system_clock::now();
        auto epoch_time = curr.time_since_epoch();
        auto s = chrono::duration_cast<chrono::seconds>(epoch_time);
        long long t = s.count(); // curr timme in seconds from epoch
        if (e.order_type=="MKT") {
            fillEvent* fill = new fillEvent(e.symbol, t, "ARCA", e.quantity, e.direction, 0, 0);
            events->push_back(fill);
        } else if (e.order_type=="LMT") { //limit order
            fillEvent* fill = book.add(e);
            events->push_back(fill);
        }
    }
}