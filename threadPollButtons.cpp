#include "threadPollButtons.h"
#include <QDebug>
#include <iostream>
extern "C"{
#include "button.h"
#include "poti.h"
#include "config.h"
#include "sensor.h"
}

using namespace std;

ThreadPollButtons::ThreadPollButtons(MainWindow *window1)
{
    window = window1;
}

void ThreadPollButtons::run()
{
    while(1){
        /* read buttons and debounce them by compare actual with old value */
        /* button T1 */
        if (digitalRead("120") == 0){
            if(state[0] == 1){
                /* perform action */
                cout << "T1\n";
                window->messure();
            }
            state[0] = 0;
        }else{
            state[0] = 1;
        }

        /* button T2 */
        if (digitalRead("121") == 0){
            if(state[1] == 1){
                /* perform action */
                cout << "T2\n";
                window->reset();
            }
            state[1] = 0;
        }else{
            state[1] = 1;
        }

        /* button T3 */
        if (digitalRead("122") == 0){
            if(state[2] == 1){
                /* perform action */
                cout << "T3\n";

                /* change selected slider */
                if(window->selectedSlider == 0){
                    window->selectedSlider = 1;
                }else{
                    window->selectedSlider = 0;
                }

            }
            state[2] = 0;
        }else{
            state[2] = 1;
        }

        /* button T4 */
        if (digitalRead("123") == 0){
            if(state[3] == 1){
                /* perform action */
                cout << "T4\n";
                window->end();
            }
            state[3] = 0;
        }else{
            state[3] = 1;
        }

        /* read poti value and convert to int */
        potiValue = readPoti() * 100;

        /* limit potiValue */
        if (potiValue > POTI_MAX){
            potiValue = POTI_MAX;
        }
        if (potiValue < POTI_MIN){
            potiValue = POTI_MIN;
        }

        /* set the integrtion time if potiValue has changed */
        if (potiValue != potiValueOld && loopDivider >= POTI_LOOP_DIVIDER){

            /* reset loopDivider */
            loopDivider = 0;

            /* change integrationTime */
            if(window->selectedSlider == 0){
                switch (potiValue / POTI_GAP_6) {
                case 0: /* biggest value */
                    cout << "integrationTime: 700ms\n";
                    setIntegationTime(TCS34725_INTEGRATIONTIME_700MS);
                    break;
                case 1:
                    cout << "integrationTime: 154ms\n";
                    setIntegationTime(TCS34725_INTEGRATIONTIME_154MS);
                    break;
                case 2:
                    cout << "integrationTime: 101ms\n";
                    setIntegationTime(TCS34725_INTEGRATIONTIME_101MS);
                    break;
                case 3:
                    cout << "integrationTime: 50ms\n";
                    setIntegationTime(TCS34725_INTEGRATIONTIME_50MS);
                    break;
                case 4:
                    cout << "integrationTime: 24ms\n";
                    setIntegationTime(TCS34725_INTEGRATIONTIME_24MS);
                    break;
                case 5: /* smallest value */
                    cout << "integrationTime: 2.4ms\n";
                    setIntegationTime(TCS34725_INTEGRATIONTIME_2_4MS);
                    break;
                default:
                    break;
                }
            }else{
                /* change gain */
                switch (potiValue / POTI_GAP_4) {
                case 0:
                    cout << "gain: 60\n";
                    setGain(TCS34725_GAIN_60X);
                    break;
                case 1:
                    cout << "gain: 16\n";
                    setGain(TCS34725_GAIN_16X);
                    break;
                case 2:
                    cout << "gain: 4\n";
                    setGain(TCS34725_GAIN_4X);
                    break;
                case 3:
                    cout << "gain: 1\n";
                    setGain(TCS34725_GAIN_1X);
                    break;
                default:
                    break;
                }
            }

            /* update display when poti value changed */
            window->update();
        }

        /* save the old potiValue */
        potiValueOld = potiValue;

        /* increment loopDivider */
        loopDivider++;

        /* do something else */
        this->usleep(100000);
    }
}
