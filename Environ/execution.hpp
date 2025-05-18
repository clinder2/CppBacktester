#ifndef EXECUTOR_H
#define EXECUTOR_H

//#include "event.hpp"
//#include "eventDatautils.hpp"
#include "MPortfolio.cpp"

using namespace std;

class executionHandler {
    public:
        virtual void execute_order(orderEvent _event)=0;
};

class simulatedExecutionHandler : public executionHandler {
    public:
        deque<event*>* events;

        simulatedExecutionHandler(deque<event*>& _events);
        void execute_order(orderEvent _event) override;
};

#endif