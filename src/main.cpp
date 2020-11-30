// demo.cpp
// How to use the motils library

#include <Arduino.h>
#include "motils.hpp"

// dummy function to simulate peripheral initialization
// this could be i.e. sensor.begin() or similar
// only rule: return type: bool
bool peripheral_begin() { return random(0, 2); }

// dummy function to simulate peripheral health check
// this could be i.e. sensor.active() or similar
// only rule: return type: bool
bool peripheral_alive() { return random(0, 2); }

// create the InitManager object
InitManager im(10);

void setup() {

    Serial.begin(115200);

    Serial.println("begin");

    // register all peripherals to be managed by im
    // peripheral name, pointer to begin function, pointer to alive function
    im.add_init("peripheral0", peripheral_begin, peripheral_alive);
    im.add_init("peripheral1", peripheral_begin, peripheral_alive);
    im.add_init("peripheral2", peripheral_begin, peripheral_alive);
    im.add_init("peripheral3", peripheral_begin, peripheral_alive);

    // set fail conditions
    // im.fail_at(ALL_FAIL); // ALL_FAIL | ONE_FAIL;

    // set fail strategy
    // im.at_fail(RETRY_UNTIL_SUCCESS); // RESET | DEATHLOOP |
    // RETRY_UNTIL_SUCCESS | no of
    // retries as int
    // or im.at_fail_cb(*cleanup); // pointer to cleanup function

    // init all peripherals, fail at fail condition and apply fail strategy
    im.init();
}

void loop() {

    // check alive state of all peripherals, fail at fail condition and apply
    // fail strategy
    im.alive();
    sleep(10);
}
