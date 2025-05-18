#ifndef WHILE_H
#define WHILE_H

//#include "event.hpp"
//#include "event.cpp"
//#include "data.hpp"
//#include "data.cpp"
//#include "portfolio.hpp"
//#include "portfolio.cpp"
//#include "MPortfolio.cpp"
//#include "strategy.hpp"
//#include "strategy.cpp"
//#include "MRStrategy.cpp"
//#include "execution.hpp"
#include "execution.cpp"

class While {
    public:
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