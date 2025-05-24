#include "complexWhile.hpp"

simulatedExecutionHandler executor = simulatedExecutionHandler();

pthread_mutex_t qlock; //lock for event queue
pthread_mutex_t executorlock; //lock for execution handler

complexWhile::complexWhile(long _start, long _end, vector<portfolio*>* _ports) {
    start=_start;
    end=_end;
    ports=_ports;
    for (auto p : *ports) {
        port_id_map[p->id]=p;
    }
    pthread_mutex_init(&qlock, NULL);
    pthread_mutex_init(&executorlock, NULL);
}

void complexWhile::while_loop_multiport() {
    deque<event*> market_q = *(new deque<event*>()); //global shared event queue
    vector<pthread_t*> port_threads;
    executor = simulatedExecutionHandler(market_q, port_id_map);
    for (auto p : *ports) {
        pthread_t id;
        loopArgs a = *(new loopArgs());
        a.start=start;
        a.end=end;
        a.port_id_map=port_id_map;
        a.q = &market_q;
        a.p = p;
        pthread_create(&id, NULL, portfolio_loop, &a);
        port_threads.push_back(&id);
    }
}

void* complexWhile::portfolio_loop(void* a) {
    loopArgs input = *(static_cast<loopArgs*>(a));
    portfolio* p = input.p;
    deque<event*>* market_q = input.q;
    long start = input.start;
    long end = input.end;
    map<long, portfolio*> port_id_map = input.port_id_map;
    if (p->strategy_type.empty()) {
        throw runtime_error("portfolio strategy not specified and LOOK WHAT YOU HAVE DONE TO ME!!!!!");
    } else if (p->p_type.empty()) {
        throw runtime_error("portfolio type not specified and LOOK WHAT YOU HAVE DONE TO ME!!!!!");
    }
    deque<event*>* q = new deque<event*>(); //individual event queue
    historicDataHandler temp(*q, start, end, p->symbol_list, "/Users/christopherlinder/Desktop/CppBacktester/HistoricData/test.csv");
    portfolio* port = nullptr;
    string p_type=p->p_type;
    if (p_type=="SIMPLE") {
        port = new naivePortfolio(&temp, *q, start);
        port = dynamic_cast<naivePortfolio*>(port);
    } else if (p_type=="MODULAR") {
        port = new MPortfolio(&temp, *q, start);
        port = dynamic_cast<MPortfolio*>(port);
    }
    string algo = p->strategy_type;
    strategy_base* s = nullptr;
    if (algo=="GA") {
        //TODO
    } else if (algo=="MA") {
        s=new MRStrategy(&temp, *q, 10);
        s=dynamic_cast<MRStrategy*>(s);
    } else if (algo=="BUYANDHOLD") {
        s=new strategy(&temp, *q);
        s=dynamic_cast<strategy*>(s);
    }
    //simulatedExecutionHandler executor(*q, port_id_map);
    bool testing = true;
    while (testing) {
        temp.update_bars();
        if (!temp.continue_backtest) {
            testing = false;
        }
        //pthread_mutex_lock(&qlock);
        while (q->size()>0) {
            event* e = q->front();
            q->pop_front();
            //pthread_mutex_unlock(&qlock);
            cout<<e->type<<"\n";
            if (e->type=="MARKET") {
                port->update_timeindex(*e);
                s->calculate_signals(*e);
                s->updateMITQ(*e);
            } else if (e->type == "SIGNAL") {
                port->update_signal(*dynamic_cast<signalEvent*>(e));
            } else if (e->type == "ORDER") {
                pthread_mutex_lock(&executorlock);
                executor.execute_order(*dynamic_cast<orderEvent*>(e));
                pthread_mutex_unlock(&executorlock);
            } else if (e->type == "FILL") {
                port->update_fill(*dynamic_cast<fillEvent*>(e));
            }
        }
        cout<<port->current_holdings["total"]<<" total\n";
    }
}