#include <avr/io.h>
#include <HardwareSerial.h>
#include "lock.h"

namespace lock {
    bool unlocked = false;

    void initialize() {
        DDRB = (1 << DDB3); // set D3 as output
    }

    void toggle(bool value) {
        unlocked = value;

        PORTB = (value << DDB3);
    }

    bool get_state() {
        return unlocked;
    }
}