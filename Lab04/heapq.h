#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include <iostream>
#include <limits.h>

 /*	Name: Declan Sheehan
  * 	Course: COSC320-001
  * 	Desc: This is where the heap class is defined
  * 	and made. It includes two chrono functions
  * 	to take the time of functions. It also defines
  * 	Expandheap, Increasekey, Insert, Maxheapify,
  * 	Extractmax, Peek, and Print.
  */

std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1, 1000000000> > > Timerstart(){
    auto start = std::chrono::system_clock::now();
    return start;
}

void Elapsedtime(std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1, 1000000000> > > start){
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Execution time: " << elapsed_seconds.count() << "\n";
}


template <class T>
class HeapQ {
private:
	template <class A>
	struct HeapObj {
		A data;
		long int key;
	};
	int space;
	int heapsize;
	int arraysize;
	HeapObj<T>* arr;
	void Expandheap (int morespace);
	void Increasekey (T A, int i, int k); // k = key
	
public:
	HeapQ();
	~HeapQ();
	void ExHp();
	void Peek();
	T Extractmax(T A);
	void Print(int i);
	void Maxheapify(T Obj, int i);
	void Insert(T obj, int priority);
};

//-----------------------------------------------------------------------

template <class T>
HeapQ<T>::HeapQ(){
	heapsize = 0;
	arraysize = 0;
	space = 16; // depth 3 default
	arr = new HeapObj<T>[space];
}

template <class T>
void HeapQ<T>::Expandheap(int morespace){
	int newspace = (this->space + morespace); // Ex: 16 + 102 = arr[118]
	HeapObj<T>* arr2 = new HeapObj<T>[newspace];
	for(int i = 1; i <= this->space; i++){
		(arr2 + i)->data = (arr + i)->data;
		(arr2 + i)->key = (arr + i)->key;
	}
	delete [] arr;
	arr = arr2;
	delete [] arr2;
	this->space = newspace;
}

template <class T>
void HeapQ<T>::ExHp(){
	int morespace;
	std::cout << "Enter an amount of space you want to add: ";
	std::cin >> morespace;
	Expandheap(morespace);
}

template <class T>
void HeapQ<T>::Increasekey(T A, int i, int k){ // A, i, k
if (k < (this->arr + i)->key) {
	std::cout << "Error: New key is smaller than old key!\n";
}
(this->arr + i)->key = k;
while (i > 1 && (this->arr + (i/2))->key < (this->arr + i)->key){
	HeapObj<T> Temp;
	Temp.key = (this->arr + i)->key;
	Temp.data = (this->arr +i)->data;
	(this->arr + i)->key = (this->arr + (i/2))->key;
	(this->arr + i)->data = (this->arr + (i/2))->data;
	(this->arr + (i/2))->key = Temp.key;
	(this->arr + (i/2))->data = Temp.data;
	i = i/2;
	}
}

template <class T>
void HeapQ<T>::Insert(T A, int priority){ // A, x
	this->heapsize = (this->heapsize + 1);
	(this->arr[this->heapsize]) = {A, (long) LONG_MIN};
	Increasekey(A,this->heapsize, priority);
}

template <class T>
void HeapQ<T>::Maxheapify(T A, int i){
	int largest;
	int l = (i*2);
	int r = (i*2+1);
	if (l <= this->heapsize && (this->arr + l)->key > (this->arr + i)->key)
			largest = l;
	else
			largest = i;
	if (r <= this->heapsize && (this->arr + r)->key > (this->arr + largest)->key)
			largest = r;
	if (largest != i){
		HeapObj<T> Temp;
		Temp.key = (this->arr + i)->key;
		Temp.data = (this->arr +i)->data;
		(this->arr + i)->key = (this->arr + (i/2))->key;
		(this->arr + i)->data = (this->arr + (i/2))->data;
		(this->arr + (i/2))->key = Temp.key;
		(this->arr + (i/2))->data = Temp.data;
		Maxheapify(A, largest);
	}
}

template <class T>
T HeapQ<T>::Extractmax(T A){
	if (this->heapsize < 1)
			std::cout << "Heap Underflow" << std::endl; // Add error perhaps.
	T max = (this->arr + 1)->data;
	(this->arr + 1)->data = (this->arr + (this->heapsize))->data;
	(this->arr + 1)->key  = (this->arr + (this->heapsize))->key;
	this->heapsize = (this->heapsize - 1);
	Maxheapify(A, 1);
	return max;
}

template <class T>
void HeapQ<T>::Peek(){
    std::cout << "Data | Key - Top of Queue" << std::endl;
    std::cout << (this->arr+1)->data  << "  |  "<< (this->arr+1)->key << std::endl;
}

template <class T>
void HeapQ<T>::Print(int a){
    for(int i = 1; i <= a; i++){
	if(i == 1 || i == 2 || i == 4 || i == 8 || i == 16 || i == 32)
	    for(int s = i; s<=a;s++)
		std::cout << " ";
	std::cout << "[" <<(this->arr + i)->data << "] "; // "|" << (this->arr + i)->key <<
	if(i == 1 || i == 3 || i == 7 || i == 15 || i == 31 || i == 63)
	    std::cout << "\n\n";
    }
    std::cout << "\n";
}

template <class T>
HeapQ<T>::~HeapQ(){
		delete arr;
}

#endif
