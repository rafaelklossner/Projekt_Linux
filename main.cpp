/*TODO
 * add thread for poll buttons (currently for c++ not working, library version missing)
 * Solve i2c-4 problem --> must touch display to continue (display also on i2c-4 bus) --> possibly solved with not shuting down x-server
 * proper clean up when pressing finish button (now it ends with segmentation fault)
 */

/* c header */
extern "C"{
#include "sensor.h"
#include "button.h"
}

/* c++ header */
#include "mainwindow.h"
#include <QApplication>
#include <QThread>
#include <iostream>
#include <threadPollButtons.h>

using namespace std;

int main(int argc, char *argv[])
{
    int status = 0;
    cout << "Starting Application Color Sensing\n";
    //initHardware();
    //status = initSensor();
    //if(status == 1){
        //configSensor();
        //startSensor();
        QApplication qApplication(argc, argv);
        ThreadPollButtons threadPollButtons;
        threadPollButtons.start();
        MainWindow window;
        window.show();

        /* stays in here until finish*/
        return qApplication.exec();
    //}
    return 0;
}
