#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <chrono>
#include <string>
#include <string>
#include "heapq.h"

/*	Name: Declan Sheehan
 * 	Course: COSC320-001
 * 	Desc: The main contains a menu, that a user can
 * 	manipulate a heap-priority-queue in realtime.
 * 	It also contains run-time tests for `Insert`.
 */

void MENU(HeapQ<std::string>* heap, int &heapsize){
    std::cout << "┌╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾┐\n";
    std::cout << "│               MENU                 │\n";
    std::cout << "│ [1] - Extract Max Object           │\n";
    std::cout << "│ [2] - Insert Name                  │\n";
    std::cout << "│ [3] - Peek At Top Priority         │\n";
    std::cout << "│ [4] - Print Out Heap               │\n";
    std::cout << "│ [5] - Exit Program                 │\n";
    std::cout << "│                                    │\n";
    std::cout << "└╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾┘\n";
    int selection = 0;
    int priority = 1;
    std::string name = "";
    while (selection < 1 || selection > 5){
	std::cout << "Selection: ";
	std::cin >> selection;
    }
	if(selection == 1){
	    if (heapsize < 1){
		std::cout << "Not enough objects in heap." << std::endl;
	    } else {
		auto start = Timerstart();
		heap->Extractmax(name);
		Elapsedtime(start);
	    }
	    //system("clear");
	    MENU(heap, heapsize);
	} else if (selection == 2){
	    int numberofnames = 0;
	    std::cout << "How many names are will you be adding?: ";
	    std::cin >> numberofnames;
	    for(int i = 0; i < numberofnames; i++){
		std::cout << "Enter a name: ";
		std::cin >> name;
		std::cout << "Enter priority for name: ";
		std::cin >> priority;
		auto start = Timerstart();
		heap->Insert(name, priority);
		Elapsedtime(start);
	    }
	    heapsize += numberofnames;
	    //system("clear");
	    MENU(heap, heapsize);
	} else if (selection == 3){
	    if (heapsize < 1) {
		std::cout << "Not enough objects in heap." << std::endl;
	    } else {
	        auto start = Timerstart();
		heap->Peek();
		Elapsedtime(start);
	    }
	    //system("clear");
	    MENU(heap, heapsize);
	} else if (selection == 4){
	    if (heapsize < 1)
		std::cout << "Not enough objects in heap." << std::endl;
	     else 
		heap->Print(heapsize);
	    MENU(heap, heapsize);
	} else if (selection == 5){
	    
	}
}

int main() {
	HeapQ<std::string>* heap = new HeapQ<std::string>();
	int heapsize = 0;
	MENU(heap, heapsize);
	
	// Expand array does not appear in the menu.
	// This is because the why would a user
	// really use it? `ExHp();` works for data types
	// that are not `std::string`. If you want to test
	// it, uncomment:
	
	// heap->ExHp();
	std::cout << "n = 10" << std::endl;
	HeapQ<long>* heap2 = new HeapQ<long>();
	auto start = Timerstart();
	for(long i = 1; i < 10;i++){
	    heap2->Insert(i,i);
	}
	Elapsedtime(start);
	std::cout << "n = 100" << std::endl;	
	HeapQ<long>* heap3 = new HeapQ<long>();
	start = Timerstart();
	for(long i = 1; i < 100;i++){
	    heap3->Insert(i,i);
	}
	Elapsedtime(start);
	std::cout << "n = 1000" << std::endl;
	HeapQ<long>* heap4 = new HeapQ<long>();
	start = Timerstart();
	for(long i = 1; i < 1000;i++){
	    heap4->Insert(i,i);
	}
	Elapsedtime(start);
	
	return 0;
}
