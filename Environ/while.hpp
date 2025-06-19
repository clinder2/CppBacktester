//#ifndef WHILE_H
//#define WHILE_H

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
//#ifndef simulatedExecutionHandler
#include "execution.hpp"
//#endif
#include "MRStrategy.hpp"
#include "MPortfolio.hpp"
#include "TSAStrategy.hpp"
#include "../Algorithms/LogReg.hpp"
#include "../Algorithms/signature.hpp"

class While {
    public:
        vector<string>* assets;
        string algo;
        long start;
        long end;
        long init_Cap;
        string p_type;

        While(vector<string>* _assets, string _algo, long _start, long _end, long _init_Cap, string _p_type);
        void while_loop();
};

//#endif