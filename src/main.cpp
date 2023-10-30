#include <avr/interrupt.h>
#include <HardwareSerial.h>
#include "hardware/keypad.h"
#include "hardware/timer.h"
#include "hardware/lock.h"
#include "api.h"

int main()
{
    sei();

    keypad::initialize();
    timer::initialize();

    lock::initialize();
    lock::toggle(false);

    api::start();

    while (1)
    {
        api::read();

        bool passed = keypad::read();

        if (passed)
            lock::toggle(true);
    }

    return 0;
}
