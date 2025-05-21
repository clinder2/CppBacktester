#include "LOB.hpp"
#include <iostream>

long HM_LOB_ID = 0;

HM_LOB::HM_LOB() {
    buy = map<long, deque<orderEvent>, greater<long> >();
    sell = map<long, deque<orderEvent> >();
    cache = map<long, orderEvent>();
}

long HM_LOB::reg_order(orderEvent o) {
    long id = HM_LOB_ID++;
    cache[id] = o;
    return id;
}

//limit order table add
fillEvent* HM_LOB::add(orderEvent o) {
    cout<<"book add\n";
    if (o.type=="LMT") { //try to buy/sell from LOB, then place in LOB
        if (o.type=="BUY") {
            long init = o.quantity;
            deque<orderEvent>& s = sell.begin()->second;
            while (o.quantity>0 && s.size()>0 && s.front().auxPrice <= o.auxPrice) { //while still willing sellers
                o.quantity=max(0, o.quantity-s.front().quantity);
                s.pop_front();
                if (s.size()==0) {
                    sell.erase(sell.begin());
                    s=sell.begin()->second;
                }
            }
            if (o.quantity>0) { //remaining buy orders, place in LOB
                if (buy.find(o.auxPrice) != buy.end()) {
                    buy[o.auxPrice].push_back(o);
                } else {
                    deque<orderEvent> curr = *(new deque<orderEvent>);
                    curr.push_back(o);
                    buy[o.auxPrice]=curr;
                }
            }
            return new fillEvent(o.symbol, 0, "A", init-o.quantity, "BUY", 0, 0);
        } else if (o.type=="SELL") {
            long init = o.quantity;
            deque<orderEvent>& b = buy.begin()->second;
            while (o.quantity>0 && b.size()>0 && b.front().auxPrice <= o.auxPrice) { //while willing buyers
                o.quantity=max(0, o.quantity-b.front().quantity);
                b.pop_front();
                if (b.size()==0) {
                    buy.erase(buy.begin());
                    b=buy.begin()->second;
                }
            }
            if (o.quantity>0) { //still sell orders
                if (sell.find(o.auxPrice) != sell.end()) {
                    sell[o.auxPrice].push_back(o);
                } else {
                    deque<orderEvent> curr = *(new deque<orderEvent>);
                    curr.push_back(o);
                    sell[o.auxPrice]=curr;
                }
            }
            return new fillEvent(o.symbol, 0, "A", init-o.quantity, "SELL", 0, 0);
        }
    } else if (o.type=="MKT") { //market order, just buy/sell
        if (o.type=="BUY") {
            deque<orderEvent>& s = sell.begin()->second;
            while (o.quantity>0 && s.size()>0 && s.front().auxPrice <= o.auxPrice) {
                o.quantity=max(0, o.quantity-s.front().quantity);
                s.pop_front();
                if (s.size()==0) {
                    sell.erase(sell.begin());
                    s=sell.begin()->second;
                }
            }
            return new fillEvent(o.symbol, 0, "A", o.quantity, "BUY", 0, 0);
        } else if (o.type=="SELL") {
            deque<orderEvent>& b = buy.begin()->second;
            while (o.quantity>0 && b.size()>0 && b.front().auxPrice <= o.auxPrice) {
                o.quantity=max(0, o.quantity-b.front().quantity);
                b.pop_front();
                if (b.size()==0) {
                    buy.erase(buy.begin());
                    b=buy.begin()->second;
                }
            }
            return new fillEvent(o.symbol, 0, "A", o.quantity, "SELL", 0, 0);
        }
    }
    fillEvent* fill = new fillEvent("DEAD", 0, "A", 0, "DEAD", 0, 0);
    fill->type="DEAD";
    return fill;
}

void HM_LOB::cancel(long id) {

}

void HM_LOB::execute(orderEvent o) {

}