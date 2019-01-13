/* c header */
extern "C"{
#include "sensor.h"
#include "button.h"
#include "poti.h"

}

/* c++ header */
#include "mainwindow.h"
#include <QApplication>
#include <QThread>
#include <iostream>
#include <threadPollButtons.h>

using namespace std;

/**
 * @brief main function of this application
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    int status = 0;

    /* inform user */
    cout << "Starting Application Color Sensing\n";

    /* init leds, buttons, poti and color sensor */
    initHardware();
    initPoti();
    status = initSensor();
    if(status == 1){
        /* config sensor with integration time and gain */
        configSensor();
        /* start messurement */
        startSensor();

        /* make a qApp with and a Window and show it */
        QApplication qApplication(argc, argv);
        MainWindow window(&qApplication);
        window.show();

        /* start a thrad to poll buttons and poti */
        ThreadPollButtons threadPollButtons(&window);
        threadPollButtons.start();

        /* app loop */
        return qApplication.exec();
    }
    return 0;
}
