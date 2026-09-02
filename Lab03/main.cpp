#include <iostream>
#include <chrono>
#include <cmath>

/* Name: Declan Sheehan
 * Course: COSC320-001
 * Desc:	The only file (main.cpp) creates a struct (heap)
 * 	with a pointer-array, length, and heapsize. It also
 * 	overloads the `[]` operator. It then has a function
 * 	to start the time (using chrono) and end the time
 * 	printing out the elapsed time in between. It has
 * 	4 functions to create fill an array in different
 * 	methods. Then it has a typical swap-function
 * 	followed by (Parent, left, & right) functions
 * 	that reflect a node given a starting point.
 * 	Lastly, it has the three functions that are
 * 	needed to heapsort the array, one to print
 * 	the end heap/array, and a function to make
 * 	fetching execution time a lot more quicker.
*/
struct heap { // heap struct based off of pseudo code.
    unsigned int* arr;
    unsigned int length;
    unsigned int heapsize;
    
    // Overload [] here?
    unsigned int& operator[] (unsigned int i){
	if(1 <= i && i <= length){
	    std::cout << "A\n";
	    return arr[i-1];
	} else {
	    std::cout << "tripped\n";
	    return arr[0];
	}
    }
};

// Yes, this long list of nonsense is the return-type.
// Starts the timer, then returns it to use later.
std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1, 1000000000> > > Timerstart(){
    auto start = std::chrono::system_clock::now();
    return start;
}

// Inputs a start time, subtracts end to start
// And prints out exec time.
void Elapsedtime(std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1, 1000000000> > > start){
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Execution time: " << elapsed_seconds.count() << "\n";
}
// Fills an array presorted.
template <typename T> void Presort(T A[], unsigned int size){
    for(T i = 1; i <= size; i++)
	A[i] = i;
}
// Fills an array reversed.
template <typename T> void Reverse(T A[], unsigned int size){
    for(T i = 1; i <= size; i++)
	A[i] = size--;
}
// Fills an array with random elements
template <typename T> void Randomized(T arr[], unsigned int min, unsigned int max, unsigned int n){
    srand (time(NULL));
    for(T i = 1; i <= n; i++){
        arr[i] = rand() % max + min;
    }
}
// Fills an array with duplicate elements.
template <typename T> void Duplicate(T arr[], unsigned int n){
    T copy;
    for(T i=1; i<=n; i++){
        arr[i] = i;
	if(n%4){
	    copy = arr[i];
	    arr[++i] = copy;
	}
    }
}
// Swaps two of anything.
template <typename T> void swap (T &A,T &B){
	T X = A;
	A = B;
	B = X;
}
// Finds the parent of a given node: i.
template <typename T> unsigned int Parent(T i){
    return (i/2);
}
// Finds the left node of a given node: i.
template <typename T> unsigned int Left (T i){
    return (2*i);
}
// Finds the right node of a given node: i.
template <typename T> unsigned int Right (T i){
    return (2*i+1);
}
// A subroutine of the PrintHeap.
template <typename T> void Print(T A[], unsigned int &i, unsigned int times){
    while (times > 0){
	std::cout << A[Left(i)] << " " << A[Right(i)] << " ";
	times--;
	i++;
    }
    std::cout << "\n";
}
// Prints a heap in a binary-tree way.
template <typename T> void PrintHeap(T A[], unsigned int depth){
    std::cout << A[1] << std::endl;
    unsigned int i = 1;
    if(depth>=2)
	std::cout << A[Left(i)] << " " << A[Right(i)] << " \n";
    i++;
    if(depth>=3){
	unsigned int times = pow(2, (depth - 2));
	unsigned int incr = 2;
	do{
	    Print(A,i,incr);
	    incr = (incr * 2);
	}while (incr <= times);
    }
}
// Heapify subroutine of HeapSort
template <typename T> void Heapify(T A[], unsigned int i, unsigned int heap_size){
    unsigned int largest;
    unsigned int l = Left(i);
    unsigned int r = Right(i);
    if (l <= heap_size && A[l] > A[i])
	largest = l;
    else 
	largest = i;
    if (r <= heap_size && A[r] > A[largest])
	largest = r;
    if (largest != i) {
	swap(A[i], A[largest]);
	Heapify(A, largest, heap_size);
    }
}
// Builds the heap.
template <typename T> void BuildHeap(T A[], unsigned int length){
    for(unsigned int i = (length/2);i>=1;i--) // A.length/2 Bottom, Down to 1.
	Heapify(A, i, length);
}
// HeapSort given the pseudocode.
template <typename T> void HeapSort(T A[], unsigned int length){
    BuildHeap(A,length);
    for(unsigned int i = length;i>=2;i--){
	swap(A[1], A[i]);
	Heapify(A,1,(i-1));
    }
}
// Function to extradite the exec time fetching.
template <typename T> void HeapSorting (T A[], unsigned int size){
    std::cout << "----------------------Size: " << size << "----------------------\nPresorted Heap Sort Time:  ";
    Presort(A, size);
    auto start = Timerstart();
    HeapSort(A, size);
    Elapsedtime(start);

    std::cout << "Reverse Heap Sort Time:    ";
    Reverse(A, size);
    start = Timerstart();
    HeapSort(A, size);
    Elapsedtime(start);
    
    std::cout << "Randomized Heap Sort Time: ";
    Randomized(A, 0, 100, size);
    start = Timerstart();
    HeapSort(A, size);
    Elapsedtime(start);
    
    std::cout << "Duplicates Heap Sort Time: ";
    Duplicate(A, size);
    start = Timerstart();
    HeapSort(A, size);
    Elapsedtime(start);
    
}

int main(){
    heap H;
    H.arr = new unsigned int[100];
    unsigned int length = 100;
    HeapSorting(H.arr, length);
    delete H.arr;
    
    H.arr = new unsigned int[1000];
    length = 1000;
    HeapSorting(H.arr, length);
    delete H.arr;
    
    H.arr = new unsigned int[10000];
    length = 10000;
    HeapSorting(H.arr, length);
    delete H.arr;
    
    H.arr = new unsigned int [100000];
    length = 100000;
    HeapSorting(H.arr, length);
    delete H.arr;
    
    H.arr = new unsigned int [1000000];
    length = 1000000;
    HeapSorting(H.arr, length);
    delete H.arr;
    
    heap K;
    K.arr = new unsigned int[15];
    for(unsigned int num = 1;num<=15;num++)
	K.arr[num] = (num+1);
    PrintHeap(K.arr,4);
    
    return 0;
}