#ifndef LOB_H
#define LOB_H

#include "DLL.hpp"
#include <map>
#include <functional>
#include <tuple>

//Class representing order for DLL, convert orderEvent into order for LOB
class order : public list_base_hook<> {
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

typedef boost::intrusive::list<order> LOBList;

class LOB {
    public:
        virtual ~LOB() {};
        virtual fillEvent add(orderEvent order)=0;
        virtual void cancel(long id)=0;
        virtual void execute(orderEvent order)=0;
};

extern long HM_LOB_ID;

class HM_LOB : LOB {
    public:
        map<long, deque<orderEvent>, greater<long> > buy;
        map<long, deque<orderEvent> > sell;

        map<long, orderEvent> cache;

        HM_LOB() {
            buy = map<long, deque<orderEvent>, greater<long> >();
            sell = map<long, deque<orderEvent> >();
            cache = map<long, orderEvent>();
        }

        long reg_order(orderEvent o) {
            long id = HM_LOB_ID++;
            cache[id] = o;
            return id;
        }
        fillEvent add(orderEvent o);
        void cancel(long id) {};
        void execute(orderEvent o) {};
};

#endif