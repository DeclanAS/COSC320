#ifndef GRAPH_H
#define GRAPH_H

#define RED "\033[1;31m"
#define ERED "\033[0m"

#define GREEN "\033[1;32m"
#define EGREEN "\033[0m"

/*	Name: Declan Sheehan
	Course: COSC320-001
	Desc: In the header file, I declare and define the
	functions for the Graph class.
*/

enum color_t{
	white, gray, black
};

struct data {
	color_t color; // Visit-state.
	int distance; // Distance from first node.
	int parent; // Previous node.
};

class Graph{
	private:
		std::map<int, std::vector<int>> vertices;
		std::list<int> node;
	public:
		Graph(); // Constructor.
		~Graph(); // Destructor.

		void addVertex(int a);
		/* 	Check to see if dupe is not entered, then add to
			the map, vertices, with an empty vector of neighbors. */
		void addEdge(int a, int b);
		/*	Should check to make sure a duplicate node isn’t entered,
		 	and then add it to the map, vertices, with an empty vector
	 		of neighbors. */
		void print(); // Prints graph.
		void printBFS(int a); // Prints graph in BFS.
};

Graph::Graph(){
	// Default Constructor.
}

Graph::~Graph(){
	// Destructor.
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
	if(v1 != v2)
		vertices[v1].push_back(v2);
	vertices[v2].push_back(v1);
}

void Graph::addVertex(int value){ // Adds a vertex to the graph.
	auto local = vertices.find(value);
	if(local == vertices.end()){
		vertices[value] = std::vector<int>();
		node.push_back(value);
	}
}

void Graph::printBFS(int s){ // Prints graph using BFS.
	printf("BFS Starting at: %d\n", s);
	std::map<int, data> curr;
	for(auto iterate = node.begin(); iterate != node.end(); iterate++){
		curr[*iterate] = data{white, -999, -1};
	}
	curr[s].color = gray;
	curr[s].distance = 0;
	std::queue<int> Que;
	Que.push(s);
	while(!Que.empty()){
		int u = Que.front();
		Que.pop();
		for(auto iterate = vertices[u].begin(); iterate != vertices[u].end(); iterate++){
			if(curr[*iterate].color == white){ // While not  discovered.
				curr[*iterate].color = gray; // Discovered.
				curr[*iterate].distance = curr[u].distance + 1; // set dist.
				curr[*iterate].parent = u; // Set parent.
				Que.push(*iterate);
				std::cout << GREEN << *iterate << EGREEN << " <-- Visited.\n";
			}
		}
		curr[u].color = black; // Finished w/ node.
	}
}

#endif
