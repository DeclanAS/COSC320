#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include "rbt.h"
#include "bt.h"

/* Name: Declan Sheehan
 * Course: COSC320-001
 * Desc: main.cpp that contains array functions, menu 
 * functions, 4 testing functions, and timing functions, 
 * 
 */


/* Testing Functions *Timestart*CustomElapsedTime* */
/* Starts the timing sequence, and returns the time element. */
#define time_datatype std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1, 1000000000> > >
time_datatype Timerstart(){ // Time start function.
	auto start = std::chrono::system_clock::now();
	return start;
}
/* Custom Elapsed Time: Takes a str for output format */
void CElapsedtime(std::string str, time_datatype start){
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << str << elapsed_seconds.count() << "s\n";
}

/*
	-The array in main is used to keep
	track of the added/removed/current
	numbers in the RBT

*/

static int position = 0; // Position var to keep track of local.
static int MAX_ARRAY_SIZE = 512; // Max size for the RBT Tree.

void addVal(int* array, int value){ // Adds value to arr.
	array[position++] = value;
}

bool Duplicate(int* array, int value){ // Checks if # is a duplicate.
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		if(array[i] == value)
			return true;
	return false;
}

bool isEmpty(int* array){ // Checks if the array is empty.
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		if(array[i] != 0)
			return false;
	return true;
}

void RemoveVal(int* array, int value){ // Removes # from array.
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		if(array[i] == value)
			array[i] = 0;
	position--;
}

int* shuffle(int n){ // Shuffles array from 1 to n.
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

void AscendingRBTest(int size){ // RBT ascending time function.
	printf("Red Black Tree [Size - %d]:\n", size);
	RBTree* T = new RBTree;

	auto start = Timerstart();
	for(int i = 0; i < size; i++)
		T->Insert(i+1);
	CElapsedtime("Insertion time: ", start);

	start = Timerstart();
	for(int i = 0; i < size; i++)
		T->Search(i+1);
	CElapsedtime("Search time: ", start);
	printf("\n");
	delete T;
}

void AscendingBTTest(int size){ // BST ascending time function.
	printf("Binary Search Tree [Size - %d]:\n", size);
	BinaryTree *T = new BinaryTree;

	auto start = Timerstart();
	for(int i = 0; i < size; i++)
		T->Insert(i+1);
	CElapsedtime("Insertion time: ", start);

	start = Timerstart();
	for(int i = 0; i < size; i++)
		T->Search(i+1);
	CElapsedtime("Search time: ", start);
	printf("\n");
	delete T;
}


void RandomRBTesting(int n){ // RBT random order time function.
	printf("Red Black Tree [Size - %d]:\n", n);
	RBTree* T = new RBTree;
	int *arr = shuffle(n);

	auto start = Timerstart();
	for(int i = 0; i < n; i++)
		T->Insert(arr[i]);
	CElapsedtime("Insertion time: ", start);

	start = Timerstart();
	for(int i = 0; i < n; i++)
		T->Search(arr[i]);
	CElapsedtime("Search time: ", start);
   delete[] arr;
	if(n == 10000)
		T->delallnil();
	printf("\n");
	delete T;
}

void RandomBTTesting(int n){ // BST random order time function.
	printf("Binary Search Tree [Size - %d]:\n", n);
	BinaryTree* T = new BinaryTree;
	int *arr = shuffle(n);

	auto start = Timerstart();
	for(int i = 0; i < n; i++)
		T->Insert(arr[i]);
	CElapsedtime("Insertion time: ", start);

	start = Timerstart();
	for(int i = 0; i < n; i++)
		T->Search(arr[i]);
	CElapsedtime("Search time: ", start);
	printf("\n");
   delete[] arr;
	delete T;
}

void MENU(RBTree *T, int* array){ // MENU Function.
	printf("┌╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾┐\n");
	printf("│               MENU                 │\n");
	printf("│ [1] - Insert                       │\n");
	printf("│ [2] - Search                       │\n");
	printf("│ [3] - Fetch Minimum                │\n");
	printf("│ [4] - Fetch Maximum                │\n");
	printf("│ [5] - Fetch Successor              │\n");
	printf("│ [6] - Delete Node                  │\n");
	printf("│ [7] - Print RBT In Orders          │\n");
	printf("│ [8] - Print Red Black Tree         │\n");
	printf("│ [9] - Exit Program                 │\n");
	printf("│                                    │\n");
	printf("└╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾┘\n");
	int selection = 0;
	int subselect = 0;
	int number = 0;

	while (selection < 1 || selection > 9){
		std::cout << "Selection:\n>";
		std::cin >> selection;
	}

	if(selection == 1){ // For Inserting a #
		do{
			printf("Enter a number (> 0) you would like to enter in the RBT:\n>");
			std::cin >> number;
		} while(Duplicate(array, number)); // Prevents duplicate insertions.
		addVal(array, number); // Adds # into array for checking.
		T->Insert(number); // Inserts
		printf("Number entered!\n");
		MENU(T, array); // Recursively calls back each time.
	} else if (selection == 2) { // Search option.
		printf("Enter a number you would like to search for:\n>");
		std::cin >> number;
		if(T->Search(number) == true)
			printf("The value does exist in the RBT!\n");
		else
			printf("The value does not exist in the RBT.\n");
		MENU(T, array);
	} else if (selection == 3) { // Minimum value option.
		if(!isEmpty(array) == true)
			printf("The minimum value in the RBT is: %d.\n", T->minimumkey());
		else
			printf("No nodes!\n");
		MENU(T, array);
	} else if (selection == 4){ // Maximum value option.
		if(!isEmpty(array) == true)
			printf("The maximum value in the RBT is: %d.\n", T->maximumkey());
		else
			printf("No nodes!\n");
		MENU(T, array);
	} else if (selection == 5){ // Successor option.
		do{
			printf("Enter a number to find the successor of:\n>");
			std::cin >> number;
		} while(!Duplicate(array, number)); // Makes sure you enter valid #
		if(!isEmpty(array) == true){
			int S = 0;
			if((S = T->Successor(number)) < 1)
				printf("Could not find the successor.\n");
			else if ((S = T->Successor(number)) == number)
				printf("Cannot find successor of %d, since it is the max value.\n", S);
			else
				printf("The successor of %d is %d.\n", number, S);
		} else {
			printf("No nodes!\n");
		}
		MENU(T, array);
	} else if (selection == 6){ // Remove node/value option.
		if(!isEmpty(array)){
			do{
				printf("Enter a number you wish to remove:\n>");
				std::cin >> number;
			} while(!Duplicate(array, number));
			RemoveVal(array, number);
			T->deleteNode(number);
			printf("Number removed!\n");
		} else
			printf("The RBT is empty!\n");
		MENU(T, array);
	} else if (selection == 7){ // Printing in diff. orders.
		printf("[1 = Inorder] [2 = Preorder] [3 = Postorder]\n");
		printf("Enter how you would like to print out the RBT:\n>");
		std::cin >> subselect;
		T->Print(subselect);
		printf("\n");
		MENU(T, array);
	} else if (selection == 8){ // Prints ~8 nodes.
		T->Printlevels();
		MENU(T, array);
	} else if (selection == 9){ // Exit menu & pgm option.
		T->delallnil(); // NEED THIS TO DEALLOCATE NIL NODE! WHY THOUGH?
		printf("Terminating Program...Bye!\n");
	}
}

int main(){
	int choice = -1;
	/* MENU OR COMPARISON MINI-MENU */
	while(choice != 1 && choice != 0){
		printf("[0]Run Menu OR \n[1]Run Comparisons?:\n>");
		std::cin >> choice;
	}
	/* RUNS MENU IF 0 */
	if(choice == 0){
		int num_array[MAX_ARRAY_SIZE];
		for(int i = 0; i < MAX_ARRAY_SIZE; i++)
			num_array[i] = 0;
		RBTree* RBT = new RBTree;
		MENU(RBT, num_array);
		delete RBT;
	} else { // RUNS COMPARISONS/TIMING.
		printf("Performing Tests:\n");
		printf("Red Black Tree Ascending Order Test\n");
		for(int i = 1000; i < 10001; i+=1000)
			AscendingRBTest(i);

		printf("Red Black Tree Random Order Test\n");
		for(int i = 1000; i < 10001; i+=1000)
			RandomRBTesting(i);

		printf("Binary Search Tree Ascending Test\n");
		for(int i = 1000; i < 10001; i+=1000)
			AscendingBTTest(i);

		printf("Binary Search Tree Random Order Test\n");
		for(int i = 1000; i < 10001; i+=1000)
			RandomBTTesting(i);
	}
	return 0;
}
