#include <initmanager.hpp>
#include <Arduino.h>
#include <Vector.h>

#define ALL_FAIL 0
#define ONE_FAIL 1

#define DEATHLOOP 0
#define RESET -1
#define RETRY_UNTIL_SUCCESS -2

InitManager::InitManager(int peripheral_count) {
    pos = 0;
    fail_count = 0;
}

void InitManager::add_init(const char *peripheral_name,
                           bool (*peripheral_begin)(),
                           bool (*peripheral_alive)()) {
    peripheral_names[pos] = peripheral_name;
    peripheral_begin_cbs[pos] = peripheral_begin;
    peripheral_alive_cbs[pos] = peripheral_alive;
    pos++;
}

void InitManager::fail_at(int fail_condition_arg) {
    // TODO: check for vaild arg
    fail_condition = fail_condition_arg;
}

void InitManager::at_fail(int fail_strategy_arg) {
    // TODO: check for vaild arg
    fail_strategy = fail_strategy_arg;
}

void InitManager::at_fail_cb(void *fail_strategy_cb_arg) {
    // TODO: check for vaild arg
    fail_strategy_cb = fail_strategy_cb_arg;
}

void InitManager::init() {
    Serial.println("init");
    for (int i = 0; i < pos; i++) {
        peripheral_states[i] = (*peripheral_begin_cbs[i])();
        Serial.print(peripheral_names[i]);
        Serial.print(" ");
        Serial.println(peripheral_states[i]);
    }
    Serial.println("re-init");
    for (int i = 0; i < pos; i++) {
        if (!peripheral_states[i]) {
            peripheral_states[i] = (*peripheral_begin_cbs[i])();
            Serial.print(peripheral_names[i]);
            Serial.print(" ");
            Serial.println(peripheral_states[i]);
        }
    }
}

void InitManager::alive() {
    Serial.println("alive");
    for (int i = 0; i < pos; i++) {
        peripheral_states[i] = (*peripheral_alive_cbs[i])();
        Serial.print(peripheral_names[i]);
        Serial.print(" ");
        Serial.println(peripheral_states[i]);
    }
}
