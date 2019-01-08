#ifndef POTI_H
#define POTI_H

void signal_callback_handler(int signum);
int initPoti(void);
void deinitPoti(void);
float readPoti(void);

#endif // POTI_H
