#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include "graph.h"

/*	Name: Declan Sheehan
	Course: COSC320-001
	Desc: The main holds a test function for each file name.
      The main(){ ... } Loops through all of the terminal-
      passed file names, and tests each of the individually.
*/

/*
   Test 1:
   Note: The DFS for this graph could also be...
   1 -> 3 -> 5 -> 5 -> 2 OR 1 -> 3 -> 2 -> 4 -> 5.

   Test 2:
   Nothing to note.

*/

void testGraph(char file_name[]){
   printf("\nTesting for graph \"%s\"\n", file_name);
   std::ifstream infile;
   infile.open(file_name);
   if(!infile){
      printf("Error opening file \"%s\"\n", file_name);
      exit(1);
   }
   char direct;
   int x1 = 0, x2 = 0;
   infile >> direct;
   Graph G(true);
   while(infile >> x1 >> x2)
      G.addEdge(x1, x2);
   infile.close();
   if(direct == 'T')
      G.setDirect(true);
   else
      G.setDirect(false);
   G.print();
   G.DFS();
   G.topSort();
   G.SCGC(); // Maybe works?
}

int main(int argc, char* argv[]){
   if(!(argc > 1)){
      printf("No file name passed!\n");
      exit(1);
   } else if (argc > 1) {
      int loop = argc - 1;
      for(int i = 0; i < loop; i++)
         testGraph(argv[i+1]);
   }
   return 0;
}
