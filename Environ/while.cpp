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
    deque<event*> q = *(new deque<event*>());
    historicDataHandler temp(q, start, end, assets, "/Users/christopherlinder/Desktop/CppBacktester/HistoricData/test.csv");
    portfolio* port = nullptr;
    if (p_type=="SIMPLE") {
        port = new naivePortfolio(&temp, q, start);
        port = dynamic_cast<naivePortfolio*>(port);
    } else if (p_type=="MODULAR") {
        port = new MPortfolio(&temp, q, start);
        port = dynamic_cast<MPortfolio*>(port);
    }
    //strategy s(&temp, q);
    strategy_base* s = nullptr;
    if (algo=="GA") {
        //TODO
    } else if (algo=="MA") {
        s=new MRStrategy(&temp, q, 10);
        s=dynamic_cast<MRStrategy*>(s);
    } else if (algo=="BUYANDHOLD") {
        s=new strategy(&temp, q);
        s=dynamic_cast<strategy*>(s);
    }
    simulatedExecutionHandler executor(q);
    bool testing = true;
    while (testing) {
        temp.update_bars();
        if (!temp.continue_backtest) {
            testing = false;
        }
        while (q.size()>0) {
            event* e = q.front();
            q.pop_front();
            cout<<e->type<<"\n";
            if (e->type=="MARKET") {
                port->update_timeindex(*e);
                s->calculate_signals(*e);
                s->updateMITQ(*e);
            } else if (e->type == "SIGNAL") {
                port->update_signal(*dynamic_cast<signalEvent*>(e));
            } else if (e->type == "ORDER") {
                executor.execute_order(*dynamic_cast<orderEvent*>(e));
            } else if (e->type == "FILL") {
                port->update_fill(*dynamic_cast<fillEvent*>(e));
            }
        }
        cout<<port->current_holdings["total"]<<" total\n";
    }
    s->plotData(2);
    cout<<executor.book.sell.size();
}