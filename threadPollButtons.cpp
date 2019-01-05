#include "threadPollButtons.h"
#include <QDebug>
#include <iostream>
extern "C"{
#include "button.h"
}

using namespace std;

ThreadPollButtons::ThreadPollButtons()
{
}

void ThreadPollButtons::run()
{
        qDebug() << "Thread Poll Button startet";

        while(1){
            cout << "poll\n";

            if (digitalRead("121") == 0){
                cout << "T1\n";
            }
            if (digitalRead("122") == 0){
                cout << "T2\n";
            }
            if (digitalRead("123") == 0){
                cout << "T3\n";
            }
            if (digitalRead("124") == 0){
                cout << "T4\n";
            }

            this->usleep(10000);
        }
}
