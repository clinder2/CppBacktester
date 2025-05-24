#include "LOB.hpp"
#include <iostream>

long HM_LOB_ID = 0;

HM_LOB::HM_LOB() {

}

HM_LOB::HM_LOB(map<long, portfolio*> _port) {
    port=_port;
    buy = map<long, deque<orderEvent*>, greater<long> >();
    sell = map<long, deque<orderEvent*> >();
    cache = map<orderEvent*, long>();
}

long HM_LOB::reg_order(orderEvent* o) {
    long id = HM_LOB_ID++;
    cache[o] = id;
    return id;
}

//limit order table add
fillEvent* HM_LOB::add(orderEvent o) {
    long id = reg_order(&o);
    cout<<buy.size()<<o.direction<<" book add\n";
    if (o.order_type=="LMT") { //try to buy/sell from LOB, then place in LOB
        if (o.direction=="BUY") {
            long init = o.quantity;
            if (sell.size()>0) {
                deque<orderEvent*>& s = sell.begin()->second;
                while (o.quantity>0 && s.size()>0 && s.front()->auxPrice <= o.auxPrice) { //while still willing sellers
                    o.quantity=max(0, o.quantity-s.front()->quantity);
                    orderEvent* filled = s.front();
                    if (filled->port >=0) {
                        port[filled->port]->update_LMT_fill(*filled); //update filled order's portfolio
                    }
                    s.pop_front();
                    if (s.size()==0) {
                        sell.erase(sell.begin());
                        s=sell.begin()->second;
                    }
                }
            }
            if (o.quantity>0) { //remaining buy orders, place in LOB
                if (buy.find(o.auxPrice) != buy.end()) {
                    buy[o.auxPrice].push_back(&o);
                } else {
                    cout<<"here\n";
                    deque<orderEvent*> curr = *(new deque<orderEvent*>);
                    curr.push_back(&o);
                    buy[o.auxPrice]=curr;
                }
            }
            return new fillEvent(o.symbol, 0, "A", init-o.quantity, "BUY", 0, 0);
        } else if (o.direction=="SELL") {
            long init = o.quantity;
            if (buy.size()>0) {
                deque<orderEvent*>& b = buy.begin()->second;
                while (o.quantity>0 && b.size()>0 && b.front()->auxPrice >= o.auxPrice) { //while willing buyers
                    o.quantity=max(0, o.quantity-b.front()->quantity);
                    orderEvent* filled = b.front();
                    if (filled->port >=0) {
                        port[filled->port]->update_LMT_fill(*filled);
                    }
                    b.pop_front();
                    if (b.size()==0) {
                        buy.erase(buy.begin());
                        b=buy.begin()->second;
                    }
                }
            }
            if (o.quantity>0) { //still sell orders
                if (sell.find(o.auxPrice) != sell.end()) {
                    sell[o.auxPrice].push_back(&o);
                } else {
                    cout<<"here\n";
                    deque<orderEvent*> curr = *(new deque<orderEvent*>);
                    curr.push_back(&o);
                    sell[o.auxPrice]=curr;
                }
            }
            cout<<buy.size()<<sell.size();
            return new fillEvent(o.symbol, 0, "A", init-o.quantity, "SELL", 0, 0);
        }
    } else if (o.order_type=="MKT") { //market order, just buy/sell
        if (o.direction=="BUY" && sell.size()>0) {
            deque<orderEvent*>& s = sell.begin()->second;
            while (o.quantity>0 && s.size()>0 && s.front()->auxPrice <= o.auxPrice) {
                o.quantity=max(0, o.quantity-s.front()->quantity);
                orderEvent* filled = s.front();
                if (filled->port >=0) {
                    port[filled->port]->update_LMT_fill(*filled);
                }
                s.pop_front();
                if (s.size()==0) {
                    sell.erase(sell.begin());
                    s=sell.begin()->second;
                }
            }
            return new fillEvent(o.symbol, 0, "A", o.quantity, "BUY", 0, 0);
        } else if (o.direction=="SELL" && buy.size()>0) {
            deque<orderEvent*>& b = buy.begin()->second;
            while (o.quantity>0 && b.size()>0 && b.front()->auxPrice <= o.auxPrice) {
                o.quantity=max(0, o.quantity-b.front()->quantity);
                orderEvent* filled = b.front();
                if (filled->port >=0) {
                    port[filled->port]->update_LMT_fill(*filled);
                }
                b.pop_front();
                if (b.size()==0) {
                    buy.erase(buy.begin());
                    b=buy.begin()->second;
                }
            }
            cout<<buy.size()<<sell.size();
            return new fillEvent(o.symbol, 0, "A", o.quantity, "SELL", 0, 0);
        }
    }
    fillEvent* fill = new fillEvent("DEAD", 0, "A", 0, "DEAD", 0, 0);
    fill->type="DEAD";
    return fill;
}

void HM_LOB::cancel(orderEvent* o) { //don't remove from LOB, tombstone marker for O(1) remove
    //orderEvent* o = cache[id];
    o->type="DEAD";
    o->symbol="DEAD";
    o->direction="DEAD";
    o->quantity=0;
    o->setAuxPrice(0);
}

void HM_LOB::execute(orderEvent o) {

}