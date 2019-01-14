#include "threadRunningLight.h"
#include "config.h"
#include <iostream>
#include <fcntl.h>
extern "C"{
#include "button.h"
}

using namespace std;

/**
 * @brief ThreadRunningLight::ThreadRunningLight constructor
 */
ThreadRunningLight::ThreadRunningLight(int var)
{
    (void) var;
}

/**
 * @brief ThreadRunningLight::run
 */
void ThreadRunningLight::run()
{
    while(1){
        digitalWrite("124", "1");
        usleep(LED_BLINK_TIME);
        digitalWrite("124", "0");
        digitalWrite("125", "1");
        usleep(LED_BLINK_TIME);
        digitalWrite("125", "0");
        digitalWrite("126", "1");
        usleep(LED_BLINK_TIME);
        digitalWrite("126", "0");
        digitalWrite("127", "1");
        usleep(LED_BLINK_TIME);
        digitalWrite("127", "0");
        usleep(LED_WAIT_TIME);
    }
}
