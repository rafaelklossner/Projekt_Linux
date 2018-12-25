/*TODO
 * add thread for poll buttons (currently for c++ not working)
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
#include <iostream>
#include <thread>
using namespace std;

pthread_t tid[2];

int main(int argc, char *argv[])
{
    int status = 0;
    cout << "Starting Application Color Sensing\n";
    initHardware();
    status = initSensor();
    if(status == 1){
        configSensor();
        startSensor();
        QApplication qApplication(argc, argv);
        MainWindow window;
        window.show();

        /* start thread for button poll */
        // Constructs the new thread and runs it. Does not block execution.
        //thread t1(runningLight, "Hello");

        // Do other things...

        // Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
        //t1.join();

        /* stays in here until finish*/
        return qApplication.exec();
    }
    return 0;
}
