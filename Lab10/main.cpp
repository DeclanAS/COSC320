#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <queue>
#include <list>
#include <map>
#include "graph.h"

/*	Name: Declan Sheehan
	Course: COSC320-001
	Desc: In the main, I declare a Graph class, add a few edges.
	From there, I print out the neighbors of each vertex and the
	BFS of that graph.
*/

void Test1(){
	Graph G;
	G.addEdge(1, 8);
	G.addEdge(7, 4);
	G.addEdge(4, 2);
	G.addEdge(2, 9);
	G.addEdge(1, 9);
	G.addEdge(10, 3);
	G.addEdge(3, 6);
	G.addEdge(6, 9);
	std::cout << "This graph is the following: " << std::endl;
	G.print();
	G.printBFS(2);
}

void Test2(){ // BFS Gives you 1, 2, 3, 4, 5...
	Graph G;
	G.addEdge(1, 2);
	G.addEdge(1, 3);
	G.addEdge(2, 4);
	G.addEdge(2, 5);
	G.addEdge(5, 8);
	G.addEdge(3, 6);
	G.addEdge(3, 7);
	std::cout << "This graph is the following: " << std::endl;
	G.print();
	G.printBFS(1);
}

int main(){
	/* SEE README OR PNG FILE FOR THE BELOW GRAPH VISUAL */
	Test1();
	Test2();
	return 0;
}
