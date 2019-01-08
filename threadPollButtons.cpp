#include "threadPollButtons.h"
#include <QDebug>
#include <iostream>
extern "C"{
#include "button.h"
#include "poti.h"
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

        float value = readPoti();
        cout << "value: " << value << "\n";

        this->usleep(100000);
    }
}
