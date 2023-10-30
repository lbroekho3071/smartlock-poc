#ifndef RANDD_API_H
#define RANDD_API_H

enum ApiAction {
    Start,
    Lock,
    Unlock
};

namespace api {
    void start();
    void read();
}

#endif //RANDD_API_H
