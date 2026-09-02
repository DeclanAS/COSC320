#include <iostream>
#include <time.h>
#include "timer.h"
// Declan Sheehan, COSC320-001
// timer.cpp Lab1
// Defines class timer in order to record a
// sorting algorithm's execution time.

using namespace std;

timer::timer(){ // Default constructor for timer.
    elapsedTime = 0.0;
}

void timer::start(){ // Starts the timer.
    elapsedTime = 0.0;
    startTime = clock();
}

float timer::timeElapsed(){ // Measures the elapsed time, and prints it out.
    endTime = clock();
    float elapsedTime = (endTime - startTime) / (float) CLOCKS_PER_SEC;
    cout << "Calculations took: " << elapsedTime << " second(s)" << endl;
    return elapsedTime;
}