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
        map<long, portfolio*> portfolios; //mapping port ids to portfolios
        HM_LOB book;

        simulatedExecutionHandler(deque<event*>& _events, map<long, portfolio*> _portfolios) {
            portfolios=_portfolios;
            events=&_events;
            book=HM_LOB(portfolios);
        }
        void execute_order(orderEvent _event);
};

#endif