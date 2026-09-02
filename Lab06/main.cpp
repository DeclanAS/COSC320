#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

   /* Name: Declan Sheehan
    * Course: COSC320
    * Desc: The main calls to compute the hiring problem
    * and the four (pre-randomized) osrting algorithms.
    */

int main () {
   srand(time(NULL));
   // Runs hiring problem from 1k to
   // 512k (doubling ea).
   HiringProblem();
   // Tests the four sorting algorithms.
   // This seg-faults.
   // See note inside "TestSorts".
   TestSorts();
   // The main isn't big enough, so:
   // int something = system("explode!");
   return 0;
}
