#ifndef WHILE_H
#define WHILE_H

#include "event.hpp"
#include "data.hpp"
#include "portfolio.hpp"
#include "portfolio.cpp"
#include "strategy.hpp"
#include "execution.hpp"

class While {
    vector<string>* assets;
    string algo;
    long start;
    long end;
    long init_Cap;
    string p_type;
    While(vector<string>* assets, string algo, long start, long end, long init_Cap, string p_type);
    void while_loop();
};

#endif