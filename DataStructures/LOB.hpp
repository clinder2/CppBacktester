#ifndef LOB_H
#define LOB_H

#include "DLL.hpp"
#include <map>
#include <functional>
#include "../Environ/event.hpp"
#include "../Environ/data.hpp"
#include "../Environ/portfolio.hpp"

extern long HM_LOB_ID;

//Class representing order for DLL, convert orderEvent into order for LOB
/* class order : public list_base_hook<> {
    public:
        string symbol;
        string order_type;
        int quantity;
        string direction;
        long auxPrice;
        long id;

        order(orderEvent o) {
            symbol=o.symbol;
            order_type=o.order_type;
            quantity=o.quantity;
            direction=o.direction;
            auxPrice=o.auxPrice;
        }
        list_member_hook<> mem_hook_;
    private:
        struct h {
            size_t operator()(const order& o) const {

            }
        };
};

typedef boost::intrusive::list<order> LOBList; */

class LOB {
    public:
        LOB();
        virtual ~LOB() {};
        virtual fillEvent* add(orderEvent order)=0;
        virtual void cancel(long id)=0;
        virtual void execute(orderEvent order)=0;
};

//extern long HM_LOB_ID=0;

class HM_LOB {
    public:
        map<long, deque<orderEvent*>, greater<long> > buy;
        map<long, deque<orderEvent*> > sell;

        map<orderEvent*, long> cache;

        map<long, portfolio*> port;

        //virtual ~HM_LOB()=0;
        HM_LOB();
        HM_LOB(map<long, portfolio*> port);
        /* HM_LOB() {
            HM_LOB_ID=0;
            buy = map<long, deque<orderEvent>, greater<long> >();
            sell = map<long, deque<orderEvent> >();
            cache = map<long, orderEvent>();
        } */

        long reg_order(orderEvent* o);
        fillEvent* add(orderEvent o);
        void cancel(orderEvent *o);
        void execute(orderEvent o);
};

#endif