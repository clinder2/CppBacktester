#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <string>
#include </Users/christopherlinder/Desktop/CppBacktester/Environ/event.hpp>

using namespace std;

class executionHandler {
    virtual void execute_order(event _event)=0;
};

class simulatedExecutionHandler : executionHandler {
    public:
        vector<event>* events;

        simulatedExecutionHandler(vector<event>* _events);
        void execute_order(event _event);
};

#endif