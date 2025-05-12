#include "while.hpp"

While::While(vector<string>* _assets, string _algo, long _start, long _end, long _init_Cap, string _p_type) {
    assets=_assets;
    algo=_algo;
    start=_start;
    end=_end;
    init_Cap=_init_Cap;
    p_type=_p_type;
}

void While::while_loop() {
    deque<event>* q = new deque<event>();
    historicDataHandler temp(q, start, end, assets, "");
    naivePortfolio* port;
    if (p_type=="SIMPLE") {
        naivePortfolio port(&temp, q, start);
    } else if (p_type=="MODULAR") {
        //TODO
    }
    strategy s(&temp, q);
    if (algo=="GA") {
        //TODO
    } else if (algo=="MA") {
        //TODO
    }
    simulatedExecutionHandler executor(q);
    bool testing = true;
    while (testing) {
        temp.update_bars();
        if (!temp.continue_backtest) {
            testing = false;
        }
        while (q->size()>0) {
            event* e = &q->front();
            q->pop_front();
            if (e->type=="MARKET") {
                port->update_timeindex(*e);
                s.calculate_signals(*e);
            } else if (e->type == "SIGNAL") {
                port->update_signal(*dynamic_cast<signalEvent*>(e));
            } else if (e->type == "ORDER") {
                executor.execute_order(*dynamic_cast<orderEvent*>(e));
            } else if (e->type == "FILL") {
                port->update_fill(*dynamic_cast<fillEvent*>(e));
            }
        }
    }
}