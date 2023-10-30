#include <HardwareSerial.h>
#include "api.h"
#include "hardware/lock.h"

#define MESSAGE_MASK 0b11

namespace api {
    void send_action(ApiAction action) {
        Serial.println(action);
    }

    void start() {
        Serial.begin(9600);

        send_action(ApiAction::Start);
    }

    void read() {
        while (Serial.available()) {
            uint8_t message = (Serial.read() & MESSAGE_MASK);

            if (message > 2)
                return;

            auto action = static_cast<ApiAction>(message);

            switch (action) {
                case Start:
                {
                    bool state = lock::get_state();
                    ApiAction new_action = state ? ApiAction::Unlock : ApiAction::Lock;

                    send_action(new_action);
                }
                    break;
                case Lock:
                    lock::toggle(false);
                    break;
                case Unlock:
                    lock::toggle(true);
                    break;
            }
        }
    }
}