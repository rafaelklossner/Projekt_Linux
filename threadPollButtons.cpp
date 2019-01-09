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
    qDebug() << "Thread Poll Button startet";

    while(1){
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

        if (digitalRead("122") == 0){
            if(state[2] == 1){
                /* perform action */
                cout << "T3\n";
            }
            state[2] = 0;
        }else{
            state[2] = 1;
        }

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

        /* set the integrtion time if potiValue has changed */
        if (potiValue != potiValueOld){
            switch (potiValue / POTI_GAP_6) {
            case 0: /* biggest value */
                cout << "0\n";
                setIntegationTime(TCS34725_INTEGRATIONTIME_700MS);
                break;
            case 1:
                cout << "1\n";
                setIntegationTime(TCS34725_INTEGRATIONTIME_154MS);
                break;
            case 2:
                cout << "2\n";
                setIntegationTime(TCS34725_INTEGRATIONTIME_101MS);
                break;
            case 3:
                cout << "3\n";
                setIntegationTime(TCS34725_INTEGRATIONTIME_50MS);
                break;
            case 4:
                cout << "4\n";
                setIntegationTime(TCS34725_INTEGRATIONTIME_24MS);
                break;
            case 5: /* smallest value */
                cout << "5\n";
                setIntegationTime(TCS34725_INTEGRATIONTIME_2_4MS);
                break;
            default:
                break;
            }
        }

        /* save the old potiValue */
        potiValueOld = potiValue;

        /* do something else */
        this->usleep(100000);
    }
}
