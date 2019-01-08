/*
 ***************************************************************************
 * \brief   Embedded Linux BTE5446 HS-2018,
 *          Basic analog to digital converter (ADC) application.
 *          Convert Analog voltage on AIN4 (Potentiometer) to Digital value.
 *
 *          D = Vin * (2^N - 1) / Vref
 *
 *          Where:
 *          D = Digital value
 *          Vin = Input voltage
 *          N = No of bits (10-Bits)
 *          Vref = reference voltage (1.8V)
 *
 * \file    appSysFsReadPoti.c
 * \version 1.0
 * \date    29.10.2013
 * \author  Martin Aebersold
 *
 * \remark  Last Modifications:
 * \remark  V1.0, AOM1, 29.10.2013   Initial release
 ***************************************************************************
 *
 * Copyright (C) 2013 Martin Aebersold, Bern University of Applied Scinces
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <math.h>

#include <sys/stat.h>

/* String to access the ADC2 via sysfs */
#define AIN2_DEV	"/sys/bus/iio/devices/iio\:device0/in_voltage2_raw"

/* Delay value for one second in us */
#define ONE_SECOND	1000000

/* Define some useful constants */
#define BUFFER_SIZE		16
#define ADC_BIT_RES		10
#define V_REF			1.8
#define N			pow(2,10)

/* Vars */
int   adc_fd;
int   charRead;
float aValue;
char  adcBuffer[BUFFER_SIZE];

/* Singnal handler for CTRL-C */
void sigint_handler(int sig);

/*
 ***************************************************************************
 * Define the function to be called when ctrl-c (SIGINT)
 * signal is sent to process
 ***************************************************************************
 */

void signal_callback_handler(int signum)
{
    /* Inform user */
    printf("\nExit via Ctrl-C\n\n");

    /* Close the adc file */
    close(adc_fd);

    /* Terminate program */
    exit(signum);
}

int initPoti(void){
    /* Register signal and signal handler */
    signal(SIGINT, signal_callback_handler);

    /* Open adc file descriptor */
    adc_fd = open(AIN2_DEV, O_RDONLY);

    /* Check for any errors */
    if (adc_fd == -1)
    {
        perror("Error: cannot open adc device!\n");
        return -1;
    }
    return 0;
}

void deinitPoti(void){
    /* Clean up and exit */
    close(adc_fd);
}

float readPoti(void){
    charRead = read(adc_fd, adcBuffer, sizeof(adcBuffer));
    if (charRead != -1){
        /* Terminate string */
        adcBuffer[charRead] = '\0';

        /* Calculate input voltage */
        aValue = (float) atoi(adcBuffer);
        aValue = (V_REF * aValue) / (N-1);
        sprintf(adcBuffer, "%f", aValue);

        /* Write input voltage to console */
        lseek(adc_fd, 0, 0);

        return aValue;
    }
    return -1;
}


