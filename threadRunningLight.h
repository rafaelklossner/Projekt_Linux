#ifndef THREADRUNNINGLIGHT_H
#define THREADRUNNINGLIGHT_H

#include <QThread>

class ThreadRunningLight :  public QThread
{
public:
    // constructor
    explicit ThreadRunningLight(int var);

    // overriding the QThread's run() method
    void run();

private:

};

#endif // THREADRUNNINGLIGHT_H
