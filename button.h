#ifndef BUTTON_H
#define BUTTON_H

void pinMode(char pin[], char mode[]);
void digitalWrite(char pin[], char value[]);
int digitalRead(char pin[]);
void cleanUp(char pin[]);
void* runningLight(void);
void* pollButtons(void);
void initHardware(void);
void deinitHardware(void);


#endif // BUTTON_H
