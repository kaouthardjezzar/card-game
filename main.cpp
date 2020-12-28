#include <iostream>
#include "examples/Bataille.h"
#include "lib/logger.h"

using namespace std;

int main() {
    LOG_INIT_CERR();
    logd.set_log_level(LOG_INFO);

    logd(LOG_DEBUG) << "Game is starting ";

    cout << "Hello, World!" << endl;

    Bataille bataille;
    bataille.lets_play();
    return 0;
}
