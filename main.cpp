#include <iostream>
#include "examples/Bataille.h"
#include "examples/HuitAmericain.h"
#include "examples/Briscola.h"


#include "lib/logger.h"

using namespace std;

int main() {
    LOG_INIT_CERR();
    logd.set_log_level(LOG_INFO);

    logd(LOG_DEBUG) << "Game is starting ";

    cout << "Hello, World!" << endl;
    HuitAmericain huitam;
    Bataille bataille;
    Briscola briscola;
    //huitam.lets_play();
    //bataille.lets_play();
    briscola.lets_playy();
    return 0;
}
