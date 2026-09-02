#include <iostream>
#include <stdlib.h>
#include <algorithm>

/*
    Name:   Declan Sheehan
    Class:  COSC320-001
    Desc:   This is the main-header file where each function is defined.
            It contains isSorted, randomizeArray, populateArray,
            dupeArray, reverseArray, Readarray, Merge, Mergesort, 
            MergeSR (subroutine), swap, partition, Quicksort,
            Timerstart, Elapsedtime, TestMerge & TestQuick.
    
*/

template <typename T> void isSorted(T* arr, long size){
    bool sorted = true;
    long i = 0;
    for(long k = 1; i < size-1; i++){
	    if(!(arr[i] < arr[k]) && arr[i] != arr[k]){
            sorted = false;
	        std::cout << "F";
            break;
        }
        k++;
    }
    if(sorted)
        std::cout << "T";
}

template <typename T> void randomizeArray(T* arr, long min, long max, long n){ // Randomizes Array.
    srand (time(NULL)); // Creates a seed.
    for(long i = 0; i < n; i++){
        arr[i] = rand() % max + min;
    }
}

template <typename T> void populateArray(T* arr, long n){
    for(long i = 0; i < n; i++)
	   arr[i] = i;

}

template <typename T> void dupeArray(T* arr, long min, long max, long n){ // Creates many duplicate elements.
    for(long i=0; i<n; i++){
        arr[i] = i;
        if ((i%4) == 0 && (i+1)<n)
            arr[++i] = arr[i-1];
    }
}

template <typename T> void reverseArray(T* arr, long n){ // Creates backwards array
    for(long i = 0; i < n; i++)
        arr[i] = n-i;
}

template <typename T> void Readarray(T* arr, long n){
    for(long i = 0; i < n; i++)
	   std::cout << arr[i] << " ";
    std::cout << "\n";
}

template <typename T> long Merge(T* arr, T* temp, long l, long mid, long h, long numofcomp){
    long i = l, j = mid + 1; // Assigns beginning of array & split point.
    
    for(long k = l; k <= h; k++) // Copies original array to a temp array.
	temp[k] = arr[k];
    
    for(long k = l; k <= h; k++) // Merges back into [l, h] array.
	if(i > mid){
	    arr[k] = temp[j++];
	    numofcomp++;
	} else if(j > h) {
	    arr[k] = temp[i++];
	    numofcomp++;
	} else if(temp[j] < temp[i]) {
	    arr[k] = temp[j++];
	    numofcomp++;
	} else {
	    arr[k] = temp[i++];
	    numofcomp++;
	}
    return numofcomp;
}
	
template <typename T> long Mergesort(T* arr, T* temp, long l, long h, long numofcomp){
    if(h <= l) // If it cannot divide down into any more elements.
	return numofcomp;
    long mid = l + (h - l)/2; // Finds mid.
    Mergesort(arr, temp, l, mid, numofcomp);
    Mergesort(arr, temp, mid+1, h, numofcomp);
    numofcomp = (numofcomp + Merge(arr, temp, l, mid, h, numofcomp));
    return numofcomp;
}

template <typename T> void MergeSR(T Endarr[], T a[], T b[], int s1, int s2, int cpr){
    int i, k, f = 0; // This function is not used.
    while(i < s1 && k < s2){
	if(a[i] < b[k]){
	    Endarr[f] = a[i];
	    cpr++;
	    i++;
	} else if (b[k] < a[i]){
	    Endarr[f] = b[k];
	    cpr++;
	    k++;
	} else {
	    Endarr[f] = a[i];
	    cpr++;
	    i++, k++;
	       }
	   f++;
    }
    
    while(i < s1){
        Endarr[f] = a[i];
        i++, f++;
    }
    while(k < s2){
        Endarr[f] = b[k];
        k++, f++;
    }
}

template <typename T> void swap(T &a, T &b){
    T x = a;
    a = b;
    b = x;
}

template <typename T> long partition(T arr[], long l, long h, long &numofswaps){
    long pivot = arr[h];
    long i = (l - 1);
    for(long j = l; j <= h - 1; j++){
	if(arr[j] < pivot){
	    i++;
	    swap(arr[i], arr[j]);
	    numofswaps++;
	   }
    }
    
    swap(arr[i + 1], arr[h]);
    numofswaps++;
    return (i + 1);
}

template <typename T> long Quicksort(T arr[], long l, long h, long &numofswaps){
if (l <= h){
    long par = partition(arr, l, h, numofswaps);
    Quicksort(arr, l, par - 1, numofswaps);
    Quicksort(arr, par + 1, h, numofswaps);
}
    return numofswaps;
}

std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1, 1000000000> > > Timerstart(){
    auto start = std::chrono::system_clock::now();
    return start;
}

void Elapsedtime(std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1, 1000000000> > > start){
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Execution time: " << elapsed_seconds.count() << "\n";
}

template <typename T> void TestMerge(T *arr, T *temp, long size){
    long numofcomp = 0;
    randomizeArray(arr, 0, 100, size);
    std::cout << "Array Size = " << size << "    | Random     | ";
    auto start = Timerstart();
    numofcomp = Mergesort(arr, temp, 0, size, numofcomp);
    Elapsedtime(start);
    std::cout << "# of comparisons: " << numofcomp << "\n";
    numofcomp = 0;
    
    dupeArray(arr, 0, 100, size);
    std::cout << "Array Size = " << size << "    | Duplicates | ";
    start = Timerstart();
    numofcomp = Mergesort(arr, temp, 0, size, numofcomp);
    Elapsedtime(start);
    std::cout << "# of comparisons: " << numofcomp << "\n";  
    numofcomp = 0;
    
    reverseArray(arr, size);
    std::cout << "Array Size = " << size << "    | Reversed   | ";
    start = Timerstart();
    numofcomp = Mergesort(arr, temp, 0, size, numofcomp);
    Elapsedtime(start);
    std::cout << "# of comparisons: " << numofcomp << "\n";
    numofcomp = 0;
    
    populateArray(arr, size);
    std::cout << "Array Size = " << size << "    | Presorted  | ";
    start = Timerstart();
    numofcomp = Mergesort(arr, temp, 0, size, numofcomp);
    Elapsedtime(start);
    std::cout << "# of comparisons: " << numofcomp << "\n";
    numofcomp = 0;
}

template <typename T> void TestQuick(T* arr, long size){
    long numofswaps = 0;
    randomizeArray(arr, 0, 100, size);
    std::cout << "Array Size = " << size << "    | Random | ";
    auto start = Timerstart();
    numofswaps = Quicksort(arr, 0, size, numofswaps);
    Elapsedtime(start);
    std::cout << "# of swaps: " << numofswaps << "\n";
    numofswaps = 0;
    
    dupeArray(arr, 0, 100, size);
    std::cout << "Array Size = " << size << "    | Duplicates | ";
    start = Timerstart();
    numofswaps = Quicksort(arr, 0, size, numofswaps);
    Elapsedtime(start);
    std::cout << "# of swaps: " << numofswaps << "\n";
    numofswaps = 0;

    reverseArray(arr, size);
    std::cout << "Array Size = " << size << "    | Reversed | ";
    start = Timerstart();
    numofswaps = Quicksort(arr, 0, size, numofswaps);
    Elapsedtime(start);
    std::cout << "# of swaps: " << numofswaps << "\n";
    numofswaps = 0;

    populateArray(arr, size);
    std::cout << "Array Size = " << size << "    | Presorted | ";
    start = Timerstart();
    numofswaps = Quicksort(arr, 0, size, numofswaps);
    Elapsedtime(start);
    std::cout << "# of swaps: " << numofswaps << "\n";

}
