#ifndef THREADPOLLBUTTONS_H
#define THREADPOLLBUTTONS_H

#include <QThread>
#include <QMainWindow>

class ThreadPollButtons :  public QThread
{
public:
    // constructor
    explicit ThreadPollButtons();

    // overriding the QThread's run() method
    void run();
};

#endif // THREADPOLLBUTTONS_H