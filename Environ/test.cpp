#include "event.hpp"
#include "while.hpp"
#include "while.cpp"
#include <boost/algorithm/algorithm.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
//#include "matplotlib-cpp/matplotlibcpp.h"
//#include "gnuplot-iostream/gnuplot-iostream.h"
//#include "/Users/christopherlinder/opt/anaconda3/pkgs/libboost-1.82.0-hf53b9f2_2/include/boost/mpi/python.hpp"

long t(string temp) {
    tm time = {};
    istringstream t(temp);
    t>>get_time(&time, "%Y-%m-%d");
    time_t epochtime = mktime(&time);
    return epochtime;
}

int main() {
    boost::ptr_vector<int> a;
    long start = t("2025-04-01");
    long end = t("2025-04-20");

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
    While w(&sym, "MA", start, end, 1000, "MODULAR");
    w.while_loop();
    return 0;
}