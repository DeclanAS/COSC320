#include <iostream>
#include <stdlib.h>
#include <chrono>
#include "main.h"

/*
	Name: 	Declan Sheehan
	Class:	COSC320-001
	Desc:	This is the main file where two dynamic array-pointers
			are created, then ran through a for-loop (to change
			array size) in order to test the two types of sorting
			algorithms four different ways (Random, Duplicated, 
			Reversed, and Presorted).

	Output Format: 
		Array Size = # | Array-Type | Exec time: ####s
		# of comparisons/swaps.
*/

int main(){
	long arraysize = 10;
	long* array;
	long* arraytemp;
	
	
	std::cout << "----------Merge Sorting----------\n"; // Tests Mergesorts.
	for(int i = 0; i < 5; i++){
		arraysize = arraysize * 10;
		array = new long[arraysize];
		arraytemp = new long[arraysize];
		TestMerge(array, arraytemp, arraysize);
		delete [] array;
		delete [] arraytemp;
	}
	
	arraysize = 10;

	
	std::cout << "----------Quick Sorting----------\n"; // Tests Quicksorts.
	for(int i = 0; i < 5; i++){
		arraysize = arraysize * 10;
		array = new long[arraysize];
		TestQuick(array, arraysize);
		delete [] array;
	}
	
}