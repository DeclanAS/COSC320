#ifndef TIMER_H
#define TIMER_H
#include <iostream>
#include <time.h>
// Declan Sheehan, COSC320-001
// timer.h Lab1
// Creates the time class and its prototype.

using namespace std;

class timer {
private:
    float elapsedTime;
    clock_t startTime;
    clock_t endTime;

public:
    void start(); // Starts time.
    
    float timeElapsed(); // Ends the time and prints the time elapsed.
    
    timer(); // Constructor for timer.
    
};

#endif