#include "LOB.hpp"
#include <iostream>

int main() {
    map<long, portfolio*> p;
    HM_LOB h(p);
    h.add(*(new orderEvent("a" ,"LMT", 1, "BUY")));
    h.add(*(new orderEvent("a" ,"LMT", 1, "BUY")));
    orderEvent a = *(new orderEvent("a" ,"LMT", 2, "BUY"));
    a.setAuxPrice(2);
    h.add(a);
    orderEvent b = *(new orderEvent("a" ,"LMT", 2, "BUY"));
    b.setAuxPrice(3);
    h.add(b);
    a.direction="SELL";
    a.setAuxPrice(1);
    h.add(a);
    //long t= h.reg_order(&a);
    cout<<"\n"<<a.type<<"\n";
    h.cancel(&a);
    cout<<a.type<<" a \n";
    return 0;
}