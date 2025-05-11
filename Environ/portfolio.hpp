#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "event.hpp"
#include "data.hpp"
#include "data.cpp"

class portfolio {
    public:
        virtual ~portfolio() {};
        virtual void update_signal(event e) {};
        virtual void update_fill(event e) {};
};

#endif