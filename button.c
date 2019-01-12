#include "button.h"
#include <stdio.h>          /* for printf */
#include <stdlib.h>         /* for exit, EXIT_FAILURE */
#include <unistd.h>         /* sleep */
#include <string.h>
#include <fcntl.h>
#include <assert.h>

int blink_period = 1000000;
int direction = 0;

/**
 * @brief set mode "in" or "out" for specific pin
 * @param pin
 * @param mode
 */
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

/**
 * @brief write value to pin
 * @param pin
 * @param value
 */
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

/**
 * @brief read value from pin
 * @param pin
 * @return
 */
int digitalRead(const char pin[]) {
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

/**
 * @brief cleanUp
 * @param pin
 */
void cleanUp(char pin[]) {
    assert(strcmp(pin,"120")==0 || strcmp(pin,"121")==0 || strcmp(pin,"122")==0  || strcmp(pin,"123")==0
            || strcmp(pin,"124")==0 || strcmp(pin,"125")==0 || strcmp(pin,"126")==0 || strcmp(pin,"127")==0);
    int fd_unexport;
    fd_unexport = open("/sys/class/gpio/unexport", O_WRONLY);
    write(fd_unexport, pin, 4);
    close(fd_unexport);
}

/**
 * @brief init all leds and buttons
 */
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
    digitalWrite("124", "0");
    digitalWrite("125", "0");
    digitalWrite("126", "0");
    digitalWrite("127", "0");
}

/**
 * @brief deinit all leds and buttons
 */
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
