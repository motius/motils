#include <Arduino.h>
#include <Vector.h>

#define ALL_FAIL 0
#define ONE_FAIL 1

#define DEATHLOOP 0
#define RESET -1
#define RETRY_UNTIL_SUCCESS -2

class InitManager {
  public:
    InitManager(int peripheral_count);
    void add_init(const char *peripheral_name, bool (*peripheral_begin)(),
                  bool (*peripheral_alive)());
    void fail_at(int fail_condition);
    void at_fail(int fail_strategy);
    void at_fail_cb(void *fail_strategy_cb);
    void init();
    void alive();

  private:
    int pos;
    int fail_condition;
    int fail_strategy;
    void *fail_strategy_cb;
    int fail_count;
    String peripheral_names[10];
    bool (*peripheral_begin_cbs[10])();
    bool (*peripheral_alive_cbs[10])();
    bool peripheral_states[10];
};
