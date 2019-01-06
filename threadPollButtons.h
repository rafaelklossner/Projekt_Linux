#ifndef THREADPOLLBUTTONS_H
#define THREADPOLLBUTTONS_H

#include "mainwindow.h"
#include <QThread>
#include <QMainWindow>

class ThreadPollButtons :  public QThread
{
public:
    // constructor
    explicit ThreadPollButtons(MainWindow *window1);

    // overriding the QThread's run() method
    void run();

private:
    //state array for debouncing */
    char state[4];

    MainWindow *window;
};

#endif // THREADPOLLBUTTONS_H
