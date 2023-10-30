#ifndef RANDD_TIMER_H
#define RANDD_TIMER_H

namespace timer {
    void initialize();

    void enable();
    void disable();
    bool get_state();
};

#endif //RANDD_TIMER_H
