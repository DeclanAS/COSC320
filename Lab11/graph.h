#ifndef GRAPH_H
#define GRAPH_H

#define RED "\033[1;31m"
#define ERED "\033[0m"

#define GREEN "\033[1;32m"
#define EGREEN "\033[0m"

/* Name: Declan Sheehan
   Course: COSC320-001
   Desc: This file contains the class Graph and
      all of its functions.
*/

enum color_t{
	white, gray, black
};

struct data {
	color_t color; // Visit-state.
	int distance; // Distance from first node.
	int parent; // Previous node.
	int end; // End time.
};

class Graph{
	private:
      int timestamp;
      bool directed;
      bool cycle_found = false;
		std::list<int> node;
      std::stack<int> DFS_Stack;
      std::map<int, std::vector<int>> vertices;
      std::map<int, std::vector<int>> reversed;
	public:
		Graph(); // Default Constructor.
      Graph(bool a); // Constructor. Never used.
		~Graph(); // Destructor.

      bool DAG();
      void DFS();
		void SCGC();
      void print();
      void topSort();
		void revGraph();
      void addVertex(int a);
      void setDirect(bool a);
		void addEdge(int a, int b);
      void SCCVisit(int a, std::map<int, data> &);
      void DFS_visit(int a, std::map<int, data>&);

};
// ############################
// ##                        ##
// ##     CLASS FUNCTIONS    ##
// ##                        ##
// ############################
Graph::Graph(){
   timestamp = 0;
   directed = false;
	// Default Constructor.
}

Graph::Graph(bool dir){
   timestamp = 0;
   directed = dir;
}

Graph::~Graph(){
	// Destructor.
}

void Graph::setDirect(bool dir){
   directed = dir;
}

void Graph::print(){ // Prints graph.
	for(auto iterate = vertices.begin(); iterate != vertices.end(); iterate++){
		std::cout << "Node: " << iterate->first << std::endl;
		std::cout << "Neighbors: >> ";
		for(int i : iterate->second){
			std::cout << RED <<  i << ERED << " ";
		}
		printf("\n");
	}
}

void Graph::addEdge(int v1, int v2){ // Adds an edge to the graph.
	addVertex(v1);
	addVertex(v2);
	if(!directed)
		vertices[v2].push_back(v1);
	vertices[v1].push_back(v2);
}

void Graph::addVertex(int value){ // Adds a vertex to the graph.
	auto local = vertices.find(value);
	if(local == vertices.end()){ // If value not found using `find`.
		vertices[value] = std::vector<int>();
		node.push_back(value);
	}
}

bool Graph::DAG(){
   if(directed == true && cycle_found == false)
      return true;
   else
      return false;
}

void Graph::DFS_visit(int n, std::map<int, data> &NODES){
   timestamp++;
   NODES[n].color = gray;
   NODES[n].distance = timestamp;
   printf("%d -> ", n);
   for(auto iterate = vertices[n].begin(); iterate != vertices[n].end(); iterate++){
      if(NODES[*iterate].color == white){
          NODES[*iterate].parent = n;
          DFS_visit(*iterate, NODES);
      } else if(NODES[*iterate].color == gray){
          cycle_found = true;
      }
   }
   timestamp++;
   NODES[n].color = black;
   NODES[n].end = timestamp;
   DFS_Stack.push(n);
}

void Graph::DFS(){
   printf("Depth First Search Method:\n");
   std::map<int, data> NODES;
   for(auto iterate = node.begin(); iterate != node.end(); iterate++)
      NODES[*iterate] = data {white, -999, -1};

   timestamp = 0;
   while(!DFS_Stack.empty())
      DFS_Stack.pop();
   for(auto iterate = node.begin(); iterate != node.end(); iterate++){
      if(NODES[*iterate].color == white) // If not visited.
         DFS_visit(*iterate, NODES);
      else if (NODES[*iterate].color == gray)
         cycle_found = true;
   }
	printf("Fin.\n");
}

void Graph::topSort(){ // Topological sort method.
   if(DAG() == true){
      printf("Topological Sort goes as follows:\n");
      std::stack<int> new_dfs = DFS_Stack;
      while(true){
         if(new_dfs.empty()){
            break;
         } else {
            printf("%d ", new_dfs.top());
            new_dfs.pop();
         }
      }
      printf("\n");
   } else {
      printf("Cannot find the topological sort this graph because ");
      printf("it is not DAG (directed & contains no cyles).\n");
   }
}

void Graph::revGraph(){ // Reverse graph method.
	for(auto iterate = reversed.begin(); iterate != reversed.end(); iterate++){
		int v1 = iterate->first;
		for(int v2 : iterate->second){
			auto local = reversed.find(v1);
	      if(local == reversed.end()) // Reverse Vertex 1
	          reversed[v1] = std::vector<int>();

			local = reversed.find(v2);
			if(local == reversed.end()) // Reverse Vertex 2
				reversed[v2] = std::vector<int>();

			if(!directed)
				 reversed[v1].push_back(v2);
			reversed[v2].push_back(v1);
		}
	}
}

void Graph::SCCVisit(int n, std::map<int, data> &NODES){
   timestamp++;
   NODES[n].color = gray;
   NODES[n].distance = timestamp;
   printf("%d -> ", n);
   for(auto iterate = vertices[n].begin(); iterate != vertices[n].end(); iterate++){
      if(NODES[*iterate].color == white){
          NODES[*iterate].parent = n;
          DFS_visit(*iterate, NODES);
      } else if(NODES[*iterate].color == gray){
          cycle_found = true;
      }
   }
   timestamp++;
   NODES[n].color = black;
   NODES[n].end = timestamp;
}

void Graph::SCGC(){ // Strongly-connected graph component.
   printf("Strongly-connected graph component:\n");
	revGraph();
	timestamp = 0;
	std::map<int, data> NODES;
   for(auto iterate = node.begin(); iterate != node.end(); iterate++)
      NODES[*iterate] = data {white, -999, -1};

   while(!DFS_Stack.empty()){
		if(NODES[DFS_Stack.top()].color == white){
			SCCVisit(DFS_Stack.top(), NODES);
		} else if (NODES[DFS_Stack.top()].color == gray) {
			cycle_found = true;
		}
		DFS_Stack.pop();
	}
	printf("Fin.\n");
}

#endif
