#include "test.hpp"
//#include "graphing/graphUtils.hpp"
//#include <boost/intrusive/list.hpp>
//#include "gnuplot-iostream/gnuplot-iostream.h"
//#include "/Users/christopherlinder/opt/anaconda3/pkgs/libboost-1.82.0-hf53b9f2_2/include/boost/mpi/python.hpp"

//namespace plt = matplotlibcpp;

long t(string temp) {
    tm time = {};
    istringstream t(temp);
    t>>get_time(&time, "%Y-%m-%d");
    time_t epochtime = mktime(&time);
    return epochtime;
}
//typedef boost::intrusive::list<orderEvent> L;
int main() {
    vector<double> y;
    y.push_back(1);
    y.push_back(2);
    //plt::plot(y);
    //plt::show();
    //boost::ptr_vector<int> a;
    long start = t("2025-01-02");
    long end = t("2025-05-12");

    deque<event>* queue = new deque<event>();
    vector<string> sym;
    /* vector<event*> te1 = *(new vector<event*>());
    signalEvent* si = new signalEvent("a",0,"a");
    orderEvent* o = new orderEvent("a", "a", 1, "a");
    event* e1 = si;
    event* e2 = o;
    //signalEvent* s2 = dynamic_cast<signalEvent*>(e1);
    vector<event*>* te = &te1;
    vector<event*> te2 = *te;
    te2.push_back(si);
    //te->push_back(o);
    //cout<<s2->type;
    for (auto v : te2) {
        cout<<v->type;
    }
    cout<<&te1<<"\n";
    cout<<&te2; */
    sym.push_back("AAPL");
    sym.push_back("IONQ");
    sym.push_back("NVDA");
    sym.push_back("PLTR");
    //cout<<sym.size();
    //While w(&sym, "MA", 0, 1, 0, "AA");
    While w(&sym, "MA", start, end, 1000, "MODULAR");
    //While w(&sym, "BUYANDHOLD", start, end, 1000, "SIMPLE");
    w.while_loop();
    return 0;
}