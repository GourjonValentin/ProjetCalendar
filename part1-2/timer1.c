//
// Created by flasque on 11/10/2023.
//

#include <stdio.h>
#include <malloc.h>
#include "timer1.h"

// start the timer
void startTimer1()
{
    _timer._start = clock();
}

// stop the timer and compute the duration in milliseconds
void stopTimer1()
{
    _timer._end = clock();
    // compute the duration in milliseconds wrt CLOCKS_PER_SEC
    _timer._msecs = (1000.0 * (double) (_timer._end - _timer._start)) / CLOCKS_PER_SEC;
}

// display the time
void displayTime1()
{
    // display the time using getTimeAsString1()
    printf("%s\n", getTimeAsString1());
    return;
}

// return a string with the time in seconds and milliseconds
char *getTimeAsString1()
{
    // return a string with the time in seconds and milliseconds
    // format : integers, with 3 digits, fill with 0
    // example : 001,123

    // use sprintf to write the string in a dynamically allocated buffer
    char *buffer = (char *)malloc(10*sizeof(char));
    // use sprintf to write the string in a dynamically allocated buffer
    sprintf(buffer, "[%g] %03d,%03d", _timer._msecs, (int)(_timer._msecs)/1000, (int)(_timer._msecs)%1000);

    // return the buffer
    return buffer;
}

int getTimeAsMsecs1()
{
    return (int)_timer._msecs;
}