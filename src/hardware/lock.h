#ifndef RANDD_LOCK_H
#define RANDD_LOCK_H

namespace lock {
    void initialize();

    void toggle(bool value);
    bool get_state();
}

#endif //RANDD_LOCK_H
