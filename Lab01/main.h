#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include "timer.h"
using namespace std;
// Declan Sheehan, COSC320-001
// main.h Lab1.
// Defines all existing functions for the main; mainly including
// sorting algorithms.

template <typename T> void populateArray(T arr[], T min, T max, int n){ // Populates Array.
    srand (time(NULL)); // Creates a seed.
    for(int i=0; i<n; i++){
        arr[i] = rand() % max + min;
    }
}

template <typename T> void reverseArray(T arr[], int n){ // Reverses Array.
    T arr_2[n];
    int max = n-1;
    for(int i=0; i<n; i++){
        arr_2[max-=1] = arr[n];
    }
    
    for(int i=0; i<n; i++)
        arr[i] = arr_2[i];
}

template <typename T> bool isSorted(T arr[], int n){ // isSorted Function.
    int l = 1;
    for(int i = 0; i < (n-1); i++){
	
	if((!(arr[i] < arr[l])) && (arr[i] != arr[l]))
	    return false;
	l++;
    }
    return true;
}

template <typename T> void bubbleSort(T arr[], int n){ // Bubble Sort Algorithm.
    int swaps = 0;
    T temp;
    int counter = 0;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(arr[i]>arr[j]){
                swap(arr[i], arr[j]);
		swaps++;
            }
        }
    }
    cout << "Number of swaps: " << swaps << "  |  ";
}

template <typename T> void insertionSort(T arr[], int n){ // Insertion Sort Algorithm.
    int swaps = 0;
    int counter = 0;
    for(int j,i = 1; i<n; i++){
        j=i;
        while (j > 0 && arr[j - 1] > arr[j]){
            swap(arr[j], arr[j-1]);
	    swaps++;
            j--;
        }
    }
    cout << "Number of swaps: " << swaps << "  |  ";
}

template <typename T> void selectionSort(T arr[], int n){ // Selection Sort Algorithm.
    int swaps = 0;
    int counter = 0;
    for(int i=0; i<n-1; i++){
        int min = i;
        for(int j = i+1; j<n; j++)
            if(arr[j] < arr[min])
                min = j;
            swap(arr[i], arr[min]);
	    swaps++;
    }
    cout << "Number of swaps: " << swaps << "  |  ";
}

void Part_one(float timeData[]){ // Executes needed objectives for part one of one project.
    timer Timer;
    int a = 100;
    int x = 0;
	cout << "----------100 Size Array----------" << endl;
        int arr[a]; // Bubble Sort with 100 elements.
        populateArray(arr, 1, a, a);
	cout << "Array is sorted : ";
	if(!(isSorted(arr, a))) // isSorted func checking whether it properly sorts.
	    cout << "False <--------------\n";
        Timer.start();
        bubbleSort(arr, a);
        timeData[x++] = Timer.timeElapsed();
	cout << "Array is sorted : ";
	if(isSorted(arr, a))
	    cout << "True <---------------\n";
	
	populateArray(arr, 1, a, a); // Insertion Sort with 100 elements.
	Timer.start();
	insertionSort(arr, a);
	timeData[x++] = Timer.timeElapsed();
	
	populateArray(arr, 1, a, a); // Selection Sort with 100 elements.
	Timer.start();
	selectionSort(arr, a);
	timeData[x++] = Timer.timeElapsed();
	
	cout << "Sorting an already sorted array using selection sort." << endl;
	Timer.start(); // Already sorted
	selectionSort(arr, a);
	timeData[x++] = Timer.timeElapsed();
	
	cout << "Sorting a reversed array using selection sort." << endl;
	reverseArray(arr, a);
	Timer.start(); // Reverse sorting
	selectionSort(arr, a);
	timeData[x++] = Timer.timeElapsed();
	
	a = a * 100;
	cout << "---------10000 Size Array---------" << endl;
	int ab[a];
	populateArray(ab, 1, a, a);
	Timer.start();
	bubbleSort(ab, a);
	timeData[x++] = Timer.timeElapsed();

	populateArray(ab, 1, a, a);
	Timer.start();
	insertionSort(ab, a);
	timeData[x++] = Timer.timeElapsed();
	
	populateArray(ab, 1, a, a);
	Timer.start();
	selectionSort(ab, a);
	timeData[x++] = Timer.timeElapsed();

	cout << "Sorting an already sorted array using selection sort." << endl;
	Timer.start();
	selectionSort(ab, a);
	timeData[x++] = Timer.timeElapsed();
	cout << "Sorting a reversed array using selection sort." << endl;
	Timer.start();
	selectionSort(ab, a);
	timeData[x++] = Timer.timeElapsed();

	a = a * 100;
	cout << "--------1000000 Size Array--------" << endl;
	int abc[a];
	populateArray(abc, 1, a, a);
	Timer.start();
	bubbleSort(abc, a);
	timeData[x++] = Timer.timeElapsed();
	
	populateArray(abc, 1, a, a);
	Timer.start();
	insertionSort(abc, a);
	timeData[x++] = Timer.timeElapsed();	
    
	populateArray(abc, 1, a, a);
	Timer.start();
	selectionSort(abc, a);
	timeData[x++] = Timer.timeElapsed();
	
	cout << "Sorting an already sorted array using selection sort." << endl;
	Timer.start();
	selectionSort(abc, a);
	timeData[x++] = Timer.timeElapsed();
	cout << "Sorting a reversed array using selection sort." << endl;
	Timer.start();
	selectionSort(abc, a);
	timeData[x++] = Timer.timeElapsed();

}

#endif