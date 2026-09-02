#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <time.h>

	/*	Name: Declan Sheehan
	 *	Course: Cosc320-001
	 *	Desc: Defines each sorting algorithm, and other
	 * misc functions for Lab 6.
	 */


#define time_datatype std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1, 1000000000> > >

//┌╼╼╾╼╾╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾┐
//│     MISC FUNCTIONS     │
//└╼╾╼╾╼╼╾╼╾╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾┘

time_datatype Timerstart(){
	auto start = std::chrono::system_clock::now();
	return start;
}

void Elapsedtime(time_datatype start){
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "Execution time: " << elapsed_seconds.count() << "s\n";
}

template <typename T> void swap (T &A,T &B){
	T X = A;
	A = B;
	B = X;
}

int* shuffle(int n){
	int *A = new int [n];
	for(int i = 0; i < n; i++)
		A[i] = -1;

	for(int i = 1; i <= n; i++){
		srand(time(NULL));
		int x = rand() % n;
		while(A[x] != -1){
				x = rand() % n;
		}
		A[x] = i;
	}
	return A;
}

void printArray(int* A, int n){
	for(int i = 0; i < n; i++)
		std::cout << A[i] << "\n";
}

float Hass(int n){
	int* A = new int[n];
	A = shuffle(n);
	int assistant = 0;
	float replacements = 0.0;
	for(int i = 1; i < n; i++){
		if(A[i] > A[assistant]){
			assistant = i;
			replacements++;

		}
	}
	//printArray(A, n);
	//std::cout << "Number of replacements for "
	//<< n << " hiring size: " << replacements << std::endl;
	delete[] A;
	return replacements;
}

void HiringProblem(){
	long n = 1000;
	float avg, rep;
	for(int i = 0; i < 10; i++){
	   for(int j = 0; j < 10; j++){
	      rep = rep + Hass(n);
	   }
	   avg = rep / 10;
	   std::cout << "Avg: " << avg << std::endl;
	   n = n * 2;
	}
}

//┌╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾┐
//│    MERGE FUNCTIONS     │
//└╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾┘

void Merge(int *arr, unsigned int start, unsigned int mid, unsigned int end){
	unsigned int i, j, k;
   int temp[end - start + 1];
   i = start;
   j = mid + 1;
   k = 0;
   while(i  <= mid && j <= end){
		if(arr[i] < arr[j]){
			temp[k] = arr[i];
			k++;
	   	i++;
		} else {
			temp[k] = arr[j];
			k++;
	   	j++;
		}
	}

	while(i <= mid){
		temp[k] = arr[i];
		k++;
		i++;
	}

	while(j <= end){
		temp[k] = arr[j];
		k++;
		j++;
	}

	for(i = start; i <= end; i++)
		arr[i] = temp[i - start];
}

// Mergesort function from pseudocode.
void Mergesort(int* arr, unsigned int start, unsigned int end){
  if(start < end){ // If it cannot divide down into any more elements.
    unsigned int mid = start + (end - start)/2; // Finds mid.
    Mergesort(arr, start, mid); // Left
    Mergesort(arr, mid + 1, end); // Right
    Merge(arr, start, mid, end); // Conjoin.
  }
}

//┌╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾┐
//│     HEAP FUNCTIONS     │
//└╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╼╾╼╾╾╼╾┘

struct Heap { // Heap struct based off of pseudo code.
    int* arr;
    unsigned int length;
    unsigned int heap_size;
};
// Finds the parent of a given node: i.
unsigned int Parent(unsigned int i){
    return ((i-1)/2);
}

// Finds the left node of a given node: i.
unsigned int Left (unsigned int i){
    return (2*i+1);
}

// Finds the right node of a given node: i.
unsigned int Right (unsigned int i){
    return (2*i+2);
}

void MaxHeapify(Heap A, unsigned int i){
   unsigned int largest;
   unsigned int l = Left(i);
   unsigned int r = Right(i);
   if (l <= A.heap_size && A.arr[l] > A.arr[i])
      largest = l;
   else
      largest = i;
   if (r <= A.heap_size && A.arr[r] > A.arr[largest])
      largest = r;
   if (largest != i) {
         swap(A.arr[i], A.arr[largest]);
         MaxHeapify(A, largest);
   }
}

void BuildMaxHeap(Heap A){
   A.heap_size = A.length;
   for(unsigned int i = (A.length/2); i>=1 ;i--) // A.length/2 Bottom, Down to 1.
      MaxHeapify(A, i);
}

void HeapSort(Heap A){
   BuildMaxHeap(A);
   for(unsigned int i = A.length; i>=2; i--){
      swap(A.arr[1], A.arr[i]);
      A.heap_size = A.heap_size - 1;
      MaxHeapify(A, 1);
   }
}
// Was used only for testing purposes.
void PrintHeap(Heap A){
   for(int i = 1; i < A.length; i++)
      std::cout << A.arr[i] << "\n";
}

//┌╼╼╾╼╾╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾┐
//│  QUICKSORT FUNCTIONS   │
//└╼╾╼╾╼╼╾╼╾╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾┘

int Partition(int* A, int l, int h){
	int p = h;
	int ind = l;
	for(int i = l; i < h; i++){
		if(A[i] < A[p]){
			swap(A[i], A[ind]);
			ind++;
		}
	}
	swap(A[p], A[ind]);
	return ind;
}

int RandomP(int* A, int l, int h){
	int p = 0;
	int temp = 0;
	int x = rand();
	p = l + x%(h-l+1);
	swap(A[h], A[p]);
	return Partition(A, l, h);
}

// If ran = true, it is randomized; vice versa.
int Quicksort(int* A, int l, int h, bool ran){
	int pi;
	if(l < h){
		if(rand)
			pi = RandomP(A, l, h);
		else
			pi = Partition(A, l, h);
		Quicksort(A, l, pi-1, ran);
		Quicksort(A, pi+1, h, ran);
	}
	return 0;
}

// This needs to be at the bottom, or it cannot
// identify the subroutines in the function.
void TestSorts(){
	auto start = Timerstart();
	Elapsedtime(start);
	/* THE FOLLOWING FOR LOOP SEG FAULTS IF I INCLUDE
	 ALL OF THE TESTS AT ONCE, OR SOMETIMES JUST HEAP.
	 WHY YOU ASK? I DO NOT REALLY KNOW. BY COMMENTING
	 OUT A FEW LINES HERE AND THERE I CAN GET THEM TO
	 WORK INDEPENDENTLY WITHOUT FAULT. IN THEORY
	 THIS CURRENT ARRANGEMENT SHOULD WORK. */
	for(unsigned int n = 10000; n <= 1000000; n+=50000){
			Heap H;
			H.arr = new int[n];
			int* A = new int[n];
			int* B = new int[n];
			int* C = new int[n];
			A = shuffle(n);

			for(int i = 0; i < n; i++)
				H.arr[i] = A[i];

			for(int i = 0; i < n; i++)
				B[i] = C[i] = A[i];

			start = Timerstart();
			Quicksort(A, 0, n, false);
			Elapsedtime(start);

			start = Timerstart();
			Quicksort(A, 0, n, true);
			Elapsedtime(start);

			start = Timerstart();
			Mergesort(A, 0, n);
			Elapsedtime(start);

			start = Timerstart();
			HeapSort(H);
			Elapsedtime(start);

			delete[] A;
			delete[] B;
			delete[] C;
			delete[] H.arr;
	}
}

#endif
