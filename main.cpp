#include "mainwindow.h"
#include <QApplication>
extern "C"{
#include "sensor.h"
}
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int status = 0;
    cout << "Starting Application Color Sensing\n";
    status = initSensor();
    cout << "1\n";
    if(status == 1){
        cout << "2\n";
        configSensor();
        startSensor();
        cout << "3\n";
        QApplication qApplication(argc, argv);
        cout << "4\n";
        MainWindow window;
        cout << "5\n";
        window.show();
        cout << "6\n";

        /* stays in here until finish*/
        return qApplication.exec();
    }
    return 0;
}
