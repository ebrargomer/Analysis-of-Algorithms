/*
* 	  ID: 150170043
*     Author: Ebrar Ömer
*/


#include <bits/stdc++.h>

using namespace std;
vector<string> parents;			//vector of parents
vector<string> childs;			//vector of childs
class Edge {
	public:
		string source;
		string destination;
		int weight;
	public:
		Edge(string source, string destination, int weight);
};

Edge::Edge(string source, string destination, int weight) {
	this->source=source;
	this->destination=destination;
	this->weight=weight;
}



class Graph {
	private:
		int numofnodes;
		vector<Edge> edges;
		
	public:
		Graph(int numofnodes){
			this->numofnodes=numofnodes;
		}
		Graph();
		void AddEdge(string source, string destination, int weight);
		void Print();
		
		vector<string> CreateParents();
		string findplace(vector<string> &parents, string vertice);
		void combine(vector<string> &parents, string sourceParent, string destinationParent);
		void print();
		void bubbleSort();
		void swap(Edge*, Edge*);
		void mykruskal();
};
//Function for print
void Graph::print() {
	int result = 0;
	
	for (vector<float>::size_type i = 0; i < this->edges.size(); i++) {
		Edge edge = this->edges[i];
		
		cout <<  edge.source << " " <<  edge.destination << " " << edge.weight<<endl;
		result += edge.weight;
	}
	cout << result << endl;
}
//Function for swap operation for bubble sort
void Graph::swap(Edge *xp, Edge *yp) 
{ 
    Edge temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
//I used bubble sort for sorting edges
void Graph::bubbleSort() 
{ 
    std::vector<float>::size_type i, j; 
    for (i = 0; i < edges.size()-1; i++)     
      
    for (j = 0; j < edges.size()-i-1; j++) 
        if (edges[j].weight > edges[j+1].weight) 
            swap(&edges[j], &edges[j+1]); 
} 

//Graph::Graph(int numofnodes) : numofnodes(numofnodes) {this->numofnodes=numofnodes }

void Graph::AddEdge(string source, string destination, int weight) {
	edges.push_back(Edge(source, destination, weight));
}

vector<string> Graph::CreateParents() {
//I used 2 vector, 1 for keep nodes as childs and 1 for parents. At the beginning I set them equal to make them parent for themselves.
	
	for (vector<float>::size_type vertice = 0; vertice < edges.size(); vertice++) {

		if(!(count(parents.begin(), parents.end(), edges[vertice].source))){ //same operation has done for source and destination for garantee
			parents.push_back(edges[vertice].source);
			childs.push_back(edges[vertice].source);
			
		}
		if(!(count(parents.begin(), parents.end(), edges[vertice].destination))){
			parents.push_back(edges[vertice].destination);
			childs.push_back(edges[vertice].destination);
		}
	}
	return parents;
}


string Graph::findplace(vector<string> &parents, string node) {
	int index=0;
	for (vector<float>::size_type i = 0; i < childs.size(); i++)
    {
        if (childs[i] == node){		
        	index=i;
            break;
		}
            
    }
	string parent=parents[index];
		//if the node have same index in both child and parent vectors, it means it is its own parent. 
		//if index are different, it has another parent.
		
	if (parent == node) { // If node is its own parent, returns the node
		return node;
	}
	else { // If node is not its own parent, returns its parent's parent
		return findplace(parents, parent);
	}
}


void Graph::mykruskal(){
	Graph newgraph(edges.size());		//created a new graph to design path
	vector<Edge> graph = edges;			//new vector for edges
	string sourceParent, destinationParent;
	CreateParents();					// set everyone to be their own parent
	vector<float>::size_type i=0;
	while((edges[i].source!="GP" )  || ((edges[i].destination).rfind("Ch",0)!=0)) i++;		//since the graph is sorted,
	Edge edge = edges[i];																	//I add first the smallest path from GP to the nearest church.
	newgraph.AddEdge(edge.source,edge.destination,edge.weight);
	
	sourceParent = findplace(parents,edges[i].source);
	destinationParent = findplace(parents,edges[i].destination);						//find the parents of source &destination

	combine(parents, sourceParent, destinationParent);									//set 2 nodes of edge in one parent(source's parent).

	for(i=0;i<edges.size();i++){
		if(edges[i].source=="Hipp") {
			if(edges[i].destination=="GP")
				break;			
		}
		
		else if(edges[i].source=="GP"){
			if(edges[i].destination=="Hipp")
				break;

		}
	}
	//Second, I add the path GP-Hipp since it is an obligation.
	
	edge = graph[i];
	newgraph.AddEdge(edge.source,edge.destination,edge.weight);
	sourceParent = findplace(parents,edges[i].source);
	destinationParent = findplace(parents,edges[i].destination);	
	combine(parents, sourceParent, destinationParent);

	for (i = 0; i < graph.size(); i++) {
		edge = graph[i];
		
		sourceParent = findplace(parents, edge.source);
		destinationParent = findplace(parents, edge.destination);
		if (sourceParent != destinationParent && edge.destination!="Hipp") { // IF a edge's parents are not equal, add them into graph. Since I sorted the edges, this works correctly.
			newgraph.AddEdge(edges[i].source,edges[i].destination,edges[i].weight);
			combine(parents, sourceParent, destinationParent);
		}
	}
	newgraph.bubbleSort();	//To print sortedly, I call bubblesort one more.
	newgraph.print();
}

//set 2 nodes of edge in one parent(source's parent).
void Graph::combine(vector<string> &parents, string sourceParent, string destinationParent) {
	int srcindex=0;
	for (vector<float>::size_type i = 0; i < parents.size(); i++)
    {
        if (parents[i] == sourceParent){
        	srcindex=i;
            break;
		}
            
    }
    int dstindex=0;
	for (vector<float>::size_type i = 0; i < parents.size(); i++)
    {
        if (parents[i] == destinationParent){
        	dstindex=i;
            break;
        	
		}
           
    }
	parents[dstindex] = parents[srcindex];

}
int main() {
	string fname;
	string start;
	string dest;
	string dist;
	string temp;
	int dis;
	cin >> fname;
	
	ifstream city_plan(fname);
	
	
	Graph graph(20);
	while(!city_plan.eof()){
			getline(city_plan, start,',');
			
			getline(city_plan, dest,',');

			getline(city_plan, dist,'\n');
						
			dis=stoi(dist);
			if(!( (start=="Hipp" && dest.rfind("Bas",0) ==0 ) || (start.rfind("Hp",0)==0 && dest.rfind("Hp",0)==0)))
			// I did not include direct connection between Hippodrome& any basilcas and any two important house.
			graph.AddEdge(start, dest, dis);
	}
	
	graph.bubbleSort();
	graph.mykruskal();

	return 0;
}
