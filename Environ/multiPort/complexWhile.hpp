#include "../While.hpp"
#include "../execution.hpp"
#include "../portfolio.hpp"
#include <unistd.h>

extern simulatedExecutionHandler executor;
extern historicDataHandler handler;
/* extern pthread_mutex_t qlock;
extern pthread_mutex_t LOBlock;
extern pthread_mutex_t executorlock; */

class complexWhile {
    public:
        long start;
        long end;
        vector<portfolio*>* ports;
        map<long, portfolio*> port_id_map;
        /* static pthread_mutex_t qlock; //lock for event queue
        static pthread_mutex_t executorlock; //lock for execution handler */

        complexWhile(long _start, long _end, vector<portfolio*>* ports);

        void while_loop_multiport();
        static void* portfolio_loop(void* a);
};

struct loopArgs {
    long start;
    long end;
    map<long, portfolio*> port_id_map;
    complexWhile* w;
    deque<event*>* q;
    portfolio* p;
};