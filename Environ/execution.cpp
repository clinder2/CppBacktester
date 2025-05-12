#include "execution.hpp"
#include <chrono>
#include <ctime>
#include <iostream>

simulatedExecutionHandler::simulatedExecutionHandler(deque<event*>& _events) {
    events=&_events;
}

void simulatedExecutionHandler::execute_order(orderEvent e) {
    if (e.type=="ORDER") {
        auto curr = chrono::system_clock::now();
        auto epoch_time = curr.time_since_epoch();
        auto s = chrono::duration_cast<chrono::seconds>(epoch_time);
        long long t = s.count(); // curr timme in seconds from epoch
        fillEvent* fill = new fillEvent(e.symbol, t, "ARCA", e.quantity, e.direction, 0, 0);
        events->push_back(fill);
    }
}