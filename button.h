#ifndef BUTTON_H
#define BUTTON_H

void pinMode(char pin[], char mode[]);
void digitalWrite(const char pin[], const char value[]);
int digitalRead(const char pin[]);
void cleanUp(char pin[]);
void initHardware(void);
void deinitHardware(void);


#endif // BUTTON_H
