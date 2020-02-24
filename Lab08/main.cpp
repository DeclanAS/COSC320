#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include "bt.h"

/*	Name: Declan Sheehan
 *	Course: COSC320-001
 *	Desc: The Main holds a recursive MENU used for testing.
 *	There are subroutines that are used for timing and for
 *	maintaining an array that prevents breaking the pgm.
 */

 #define time_datatype std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1, 1000000000> > >

 time_datatype Timerstart(){
 	auto start = std::chrono::system_clock::now();
 	return start;
 }

 void Elapsedtime(time_datatype start){
 	auto end = std::chrono::system_clock::now();
 	std::chrono::duration<double> elapsed_seconds = end-start;
 	std::cout << "Execution time: " << elapsed_seconds.count() << "s\n";
 }

/* -The array in main is used to keep
	track of the added/removed/current
	numbers in the BST

	-Here we assume an array full of 0's
	is an empty array */

static int position = 0;

void addVal(int* array, int value){
	array[position++] = value;
}

bool Duplicate(int* array, int value){
	for(int i = 0; i < 128; i++)
		if(array[i] == value)
			return true;
	return false;
}

bool isEmpty(int* array){
	for(int i = 0; i < 128; i++)
		if(array[i] != 0)
			return false;
	return true;
}
void RemoveVal(int* array, int value){
	for(int i = 0; i < 128; i++)
		if(array[i] == value)
			array[i] = 0;
	position--;
}

int* shuffle(int n){
	int *A = new int[n];
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


void MENU(BinaryTree *T, int* array){
	std::cout << "┌╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾┐\n";
	std::cout << "│               MENU                 │\n";
	std::cout << "│ [1] - Insert                       │\n";
	std::cout << "│ [2] - Search                       │\n";
	std::cout << "│ [3] - Fetch Minimum                │\n";
	std::cout << "│ [4] - Fetch Maximum                │\n";
	std::cout << "│ [5] - Fetch Successor              │\n";
	std::cout << "│ [6] - Delete Node                  │\n";
	std::cout << "│ [7] - Print Binary Search Tree     │\n";
	std::cout << "│ [8] - Exit Program                 │\n";
	std::cout << "│                                    │\n";
	std::cout << "└╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾┘\n";
	int selection = 0;
	int subselect = 0;
	int number = 0;

	while (selection < 1 || selection > 8){
		std::cout << "Selection: ";
		std::cin >> selection;
	}

	if(selection == 1){
		do{
			printf("Enter a number (> 0) you would like to enter in the BST: ");
			std::cin >> number;
		} while(Duplicate(array, number));
		addVal(array, number);
		T->Insert(number);
		// system("clear");
		printf("Number entered!\n");
		MENU(T, array);
	} else if (selection == 2) {
			printf("Enter a number you would like to search for: ");
			std::cin >> number;
		if(T->Search(number) != NULL)
			printf("The value does exist in the BST!\n");
		else
			printf("The value does not exist in the BST.\n");
		// system("clear");
		MENU(T, array);
	} else if (selection == 3) {
		printf("The minimum value in the BST is: %d.\n", T->minimum());
		MENU(T, array);
	} else if (selection == 4){
		printf("The maximum value in the BST is: %d.\n", T->maximum());
		MENU(T, array);
	} else if (selection == 5){
		do{
			printf("Enter a number to find the successor of: ");
			std::cin >> number;
		} while(!Duplicate(array, number));
		// system("clear");
		int S = 0;
		if((S = T->Successor(number)) == -999)
			printf("Could not find the successor.\n");
		else
			printf("The successor of %d is %d.\n", number, S);
		MENU(T, array);
	} else if (selection == 6){
		if(!isEmpty(array)){
			do{
				printf("Enter a number you wish to remove: ");
				std::cin >> number;
			} while(!Duplicate(array, number));
			RemoveVal(array, number);
			T->Deleteus(number);
			printf("Number removed!\n");
		} else
			printf("The BST is empty!\n");
		MENU(T, array);
	} else if (selection == 7){
		printf("[1 = Inorder] [2 = Preorder] [3 = Postorder]\n");
		printf("Enter how you would like to print out the BST: ");
		std::cin >> subselect;
		T->Ordering(subselect);
		printf("\n");
		MENU(T, array);
	} else if (selection == 8){
		printf("Exiting program...\n");
	}
}

void Timing(int n){
		printf("Testing Insert & Search at size: %d.\n", n);
		BinaryTree *X = new BinaryTree;
		int number = n;
		int *arr = shuffle(number);

		auto start = Timerstart();
		for(int i = 0; i < number; i++)
			X->Insert(arr[i]);
		Elapsedtime(start);

		start = Timerstart();
		for(int i = 0; i < number; i++)
			X->Search(arr[i]);
		Elapsedtime(start);
      delete[] arr;
		delete X;
}

int main(){

   char option = '~';
   while(option != '1' && option != '2'){
      printf("Run:\n");
      printf("1. BT Menu\n2. BT Timing\n>");
      std::cin >> option;
      if(option != '1' && option != '2')
         printf("Invalid input, re-enter.\n>");
   }

   if(option == '1'){
      int array[128];
      for(int i = 0; i < 128; i++)
         array[i] = 0;
      BinaryTree *T = new BinaryTree;
      MENU(T, array);
      delete T;
   } else {
      auto start = Timerstart();
      Elapsedtime(start);
      printf("Ignore Above Timing\n");
      Timing(1000);
      Timing(2000);
      Timing(3000);
      Timing(4000);
      Timing(5000);
      Timing(6000);
      Timing(7000);
      Timing(8000);
      Timing(9000);
      Timing(10000);
   }
   return 0;
}
