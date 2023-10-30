#include <avr/io.h>
#include <HardwareSerial.h>
#include "timer.h"
#include "keypad.h"
#include "lock.h"

#define COLUMN_MASK 0b11100000
#define ROW_MASK_RIGHT 0b00011100
#define ROW_MASK_LEFT 0b00000001

#define INPUT_LENGTH 5

char keys[4][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '#'},
};

namespace keypad {
    static char input[INPUT_LENGTH];
    static char CODE[] = "1478";

    void initialize() {
        DDRD = (1 << DDD7) | (1 << DDD6) | (1 << DDD5); // set D(6 - 7) as output
        PORTD = (1 << DDD7) | (1 << DDD6) | (1 << DDD5); // put 5v on D(6 - 7)

        DDRD |= (0 << DDD4) | (0 << DDD3) | (0 << DDD2) | (0 << DDD0); // set D(2 - 5) as input
        PORTD = (1 << DDD4) | (1 << DDD3) | (1 << DDD2) | (1 << DDD0); // enable pull up resistors on D(2 - 5)
    }

    void reset() {
        for (int i = 0; i < INPUT_LENGTH - 1; i++) {
            input[i] = 0;
        }
    }

    bool add_key(char key) {
        if (key == '#') {
            lock::toggle(false);

            return false;
        }

        if (key == '*') {
            reset();

            return false;
        }

        for (int i = 0; i < INPUT_LENGTH - 1; i++) {
            if ((uint8_t) input[i] == 0) {
                input[i] = key;

                if (i != (INPUT_LENGTH - 2))
                    return false;
            }
        }

        bool passed = !strcmp(CODE, input);
        reset();

        return passed;
    }

    bool read() {
        uint8_t row = ((~PIND & ROW_MASK_RIGHT) >> 1) | (~PIND & ROW_MASK_LEFT);

        if (row == 0)
            return false;

        if (timer::get_state()) {
            timer::enable();

            return false;
        }

        timer::enable();

        DDRD = (1 << DDD4) | (1 << DDD3) | (1 << DDD2) | (1 << DDD0); // set D(2 - 5) as output
        DDRD |= (0 << DDD7) | (0 << DDD6) | (0 << DDD5); // set D(6 - 7) as input

        uint8_t column = ((PIND & COLUMN_MASK) >> 5) / 2;

        row = row / 2;
        if (row > 3)
            row = 3;

        initialize();

        return add_key(keys[row][column]);
    }
}