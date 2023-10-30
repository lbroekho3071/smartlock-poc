#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

namespace timer {
    bool enabled = false;

    void initialize() {
        TCCR0A = (0 << WGM01) | (0 << WGM00); // set waveform generation mode to normal
        TIMSK0 = (1 << TOIE0); // enable timer overflow interrupt
    }

    void enable() {
        TCCR0B = (1 << WGM02) | (1 << CS02) | (1 << CS00); // set prescaler to 1024 thus enabling timer
        TCNT0 = 0;

        enabled = true;
    }

    void disable() {
        TCCR0B = (1 << WGM02) | (0 << CS02) | (0 << CS00); // set no clock source thus disabling timer

        enabled = false;
    }

    bool get_state() {
        return enabled;
    }
}

ISR(TIMER0_OVF_vect) {
    timer::disable();
}