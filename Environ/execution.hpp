#ifndef EXECUTOR_H
#define EXECUTOR_H

//#include "event.hpp"
#include "eventDatautils.hpp"
#include "../DataStructures/LOB.hpp"
//#include "portfolio.hpp"

using namespace std;

class executionHandler {
    public:
        //virtual ~executionHandler()=0;
        virtual void execute_order(orderEvent _event)=0;
};

class simulatedExecutionHandler : public executionHandler {
    public:
        deque<event*>* events;
        HM_LOB book;

        simulatedExecutionHandler(deque<event*>& _events) {
            events=&_events;
            book=HM_LOB();
        }
        void execute_order(orderEvent _event);
};

#endif