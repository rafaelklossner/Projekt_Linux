#include "button.h"
#include <pthread.h>        /* posix threads */
#include <stdio.h>          /* for printf */
#include <stdlib.h>         /* for exit, EXIT_FAILURE */
#include <unistd.h>         /* sleep */
#include <string.h>
#include <fcntl.h>
#include <assert.h>

int blink_period = 1000000;
int direction = 0;

void pinMode(char pin[], char mode[]) {
    assert(strcmp(pin,"120")==0 || strcmp(pin,"121")==0 || strcmp(pin,"122")==0  || strcmp(pin,"123")==0
            || strcmp(pin,"124")==0 || strcmp(pin,"125")==0 || strcmp(pin,"126")==0 || strcmp(pin,"127")==0);
    assert(strcmp(mode,"out")==0 || strcmp(mode,"in")==0);
    int fd_export;
    int fd_direction;
    char path[40] = "";
    fd_export = open("/sys/class/gpio/export", O_WRONLY);
    usleep(10000);
    write(fd_export, pin, 4);
    close(fd_export);

    /* Change String for direction /sys/class/gpio/gpio17/direction */
    strcpy(path, "/sys/class/gpio/gpio");
    strcat(path, pin);
    strcat(path, "/direction");

    fd_direction = open(path, O_WRONLY);
    write(fd_direction, mode, 4);
    close(fd_direction);
}

void digitalWrite(char pin[], char value[]) {
    assert(strcmp(pin,"120")==0 || strcmp(pin,"121")==0 || strcmp(pin,"122")==0  || strcmp(pin,"123")==0
            || strcmp(pin,"124")==0 || strcmp(pin,"125")==0 || strcmp(pin,"126")==0 || strcmp(pin,"127")==0);
    assert(strcmp(value,"0")==0 || strcmp(value,"1")==0);
    char path[40];
    int fd_value;
    strcpy(path, "/sys/class/gpio/gpio");
    strcat(path, pin);
    strcat(path, "/value");

    fd_value = open(path, O_WRONLY);
    write(fd_value, value, 2);
    close(fd_value);
}

int digitalRead(char pin[]) {
    assert(strcmp(pin,"120")==0 || strcmp(pin,"121")==0 || strcmp(pin,"122")==0  || strcmp(pin,"123")==0
            || strcmp(pin,"124")==0 || strcmp(pin,"125")==0 || strcmp(pin,"126")==0 || strcmp(pin,"127")==0);
    char path[40];
    int fd_value;
    char value_buffer[5];
    int value;
    strcpy(path, "/sys/class/gpio/gpio");
    strcat(path, pin);
    strcat(path, "/value");

    fd_value = open(path, O_RDONLY);
    //lseek(fd_value, 0, SEEK_SET);
    read(fd_value, value_buffer, 5);
    close(fd_value);
    value = atoi(value_buffer);
    return value;
}

void cleanUp(char pin[]) {
    assert(strcmp(pin,"120")==0 || strcmp(pin,"121")==0 || strcmp(pin,"122")==0  || strcmp(pin,"123")==0
            || strcmp(pin,"124")==0 || strcmp(pin,"125")==0 || strcmp(pin,"126")==0 || strcmp(pin,"127")==0);
    int fd_unexport;
    fd_unexport = open("/sys/class/gpio/unexport", O_WRONLY);
    write(fd_unexport, pin, 4);
    close(fd_unexport);
}

void* runningLight(void){
    while(1){
        if(direction == 0){
            digitalWrite("127", "0");
            digitalWrite("124", "1");
            usleep(blink_period);
            digitalWrite("124", "0");
            digitalWrite("125", "1");
            usleep(blink_period);
            digitalWrite("125", "0");
            digitalWrite("126", "1");
            usleep(blink_period);
            digitalWrite("126", "0");
            digitalWrite("127", "1");
            usleep(blink_period);
        }else{
            digitalWrite("124", "0");
            digitalWrite("127", "1");
            usleep(blink_period);
            digitalWrite("127", "0");
            digitalWrite("126", "1");
            usleep(blink_period);
            digitalWrite("126", "0");
            digitalWrite("125", "1");
            usleep(blink_period);
            digitalWrite("125", "0");
            digitalWrite("124", "1");
            usleep(blink_period);
        }
    }
    return NULL;
}

void* pollButtons(void){
    while(1){
        if (digitalRead("121") == 0){
            if(blink_period > 62500){
                blink_period /= 2;
            }
        }
        if (digitalRead("122") == 0){
            if(blink_period < 1000000){
                blink_period *= 2;
            }
        }
        if (digitalRead("123") == 0){
            digitalWrite("124", "0");
            digitalWrite("125", "0");
            digitalWrite("126", "0");
            digitalWrite("127", "0");
            if(direction == 0){
                direction = 1;
            }else{
                direction = 0;
            }
        }
        usleep(100000);
    }
    return NULL;
}

void initHardware(void){
    printf("init hardware\n");
    pinMode("124", "out");
    pinMode("125", "out");
    pinMode("126", "out");
    pinMode("127", "out");
    pinMode("120", "in");
    pinMode("121", "in");
    pinMode("122", "in");
    pinMode("123", "in");
    digitalWrite("124", "1");
    digitalWrite("125", "1");
    digitalWrite("126", "1");
    digitalWrite("127", "1");
}

void deinitHardware(void){
    printf("deinit hardware\n");
    digitalWrite("124", "0");
    digitalWrite("125", "0");
    digitalWrite("126", "0");
    digitalWrite("127", "0");
    cleanUp("120");
    cleanUp("121");
    cleanUp("122");
    cleanUp("123");
    cleanUp("124");
    cleanUp("125");
    cleanUp("126");
    cleanUp("127");
}
