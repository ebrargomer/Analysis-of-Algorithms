/*
* 	  ID: 150170043
*     Author: Ebrar Ömer
*/

#include <bits/stdc++.h>

using namespace std;

void DijkstrasTest();


class Node;
class Edge;
vector<Node*> nodes;	//vector of nodes
vector<Edge*> edges;	//vector of edges

class Node {
    public:
    	
		string id;
		Node* previous;
		int distance;
		
	    Node(string id){
		  	this->id=id;
		  	this->previous=NULL;
		  	this->distance=10000000; // First set distance to intinite
		  	nodes.push_back(this);   // add vector of nodes
  }

};

class Edge {
	
	
    public:
	    Node* node1;
		Node* node2;
		int distance;
		Edge(Node* node1, Node* node2, int distance){
		  	this->node1=node1;
		  	this->node2=node2;
		  	this->distance=distance;
		  	edges.push_back(this);
    }
    bool conction(Node* node1, Node* node2) {
	  	if((node1 == this->node1 && node2 == this->node2) ||  (node1 == this->node2 && node2 == this->node1))
	    return true;
	    else return false;
    }

 
};


bool isExist(vector<Node*>& nodes, Node* node) { // check if node exists
  vector<float>::size_type size = nodes.size();
  for (vector<float>::size_type i = 0; i < size; ++i) {
    if (node == nodes.at(i)) {
      return true;
    }
  }
  return false;
}

Node* findthesmallest(vector<Node*>& nodes) { //find the smallest node
  vector<float>::size_type size = nodes.size();
  int smallestindex = 0;
  if (size == 0) return NULL;		//catch exception
  
  Node* tempsmall = nodes.at(0);	//temp smallest is first node
  
  for (vector<float>::size_type i = 1; i < size; ++i) {
    Node* itr = nodes.at(i);
    if (itr->distance < tempsmall->distance) { // if athor node's distance is small change smallest
      tempsmall = itr;
      smallestindex = i;
    }
  }
  nodes.erase(nodes.begin() + smallestindex); // delete the smallest to add path and not compare again
  return tempsmall;
}

//function to find connection of the given node
vector<Node*>* connectednodes(Node* node) {
	
  vector<Node*>* newnodes = new vector<Node*>;
  
  for (vector<float>::size_type i = 0; i <  edges.size(); ++i) {
  	
    Edge* edge = edges.at(i);
    Node* connects = NULL;
    
    if (edge->node1 == node)    	connects = edge->node2;
    else if (edge->node2 == node)   connects = edge->node1;  
    if (connects && isExist(nodes, connects))  newnodes->push_back(connects);
    
  }
  return newnodes;
}

//function to find distance
int Distance(Node* node1, Node* node2) {
	
  for (vector<float>::size_type i = 0; i < edges.size(); ++i) {
    Edge* edge = edges.at(i);
    if (edge->conction(node1, node2)) {
      return edge->distance;
    }
  }
  return 0;
}



//function for print
void print(Node* lastnode) {
	Node* iterator = lastnode;
	vector<string> temp;
	
    while (iterator) {
	  	temp.push_back( iterator->id);
	    iterator = iterator->previous;
	}
// since I created the iterator vector from last to beginning, I print it reverse order
	reverse(temp.begin(), temp.end());
	for(vector<float>::size_type i=0;i<temp.size();i++)
	cout  << temp[i]<<" ";
	cout << lastnode->distance << endl;
}

void mydijkstras() {
	int distance=0;
	Node* smallest=NULL;
	Node* cn= NULL;		//temp 2 node
	vector<Node*>* connectedNodes; 
    while (nodes.size() > 0) {
		smallest = findthesmallest(nodes); //find smallest node and its connected nodes
    	connectedNodes = connectednodes(smallest);

    for (vector<float>::size_type i = 0; i < connectedNodes->size(); ++i) {
        cn = connectedNodes->at(i);
        distance = Distance(smallest, cn) + smallest->distance; //add distance to path

      if (distance < cn->distance) {
        cn->distance = distance;
        cn->previous = smallest;
      }
    }
    delete connectedNodes;
  }
}
int main() {
	string fname;
	string start;
	string dest;
	string dist;
	string temp;
	int dis;
	cin >> fname;
	vector <string> checklist;
	ifstream city_plan(fname);
	
	while(!city_plan.eof()){
			getline(city_plan, start,',');	
			getline(city_plan, dest,',');
			getline(city_plan, dist,'\n');
			dis=stoi(dist);
			if(!(find(checklist.begin(), checklist.end(), start) != checklist.end() ))
			checklist.push_back(start);
			if(!(find(checklist.begin(), checklist.end(), dest) != checklist.end() ))
			checklist.push_back(dest);
		} // first I read the nodes, to not do any duplicate keep them in a vector named checklist
	city_plan.clear();
	city_plan.seekg(0);
	string popup=" ";
	while(!city_plan.eof()){
			
			getline(city_plan, start,',');	
			getline(city_plan, dest,',');
			getline(city_plan, dist,'\n');
			dis=stoi(dist);
			if(  (start.rfind("E",0)==0) && dis<5)	popup=dest;
			else if( (dest.rfind("E",0)==0) && dis<5)	popup = start;	
			if(popup!=" "){
				for(vector<float>::size_type k=0;k<checklist.size();k++) {
					if(checklist.at(k)==popup) checklist.erase(checklist.begin() + k);
				}
			}
			popup=" ";

	 }//if any node has smaller distance to an enemy area, I pop them from checklist
	
	for(vector<float>::size_type k=0;k<checklist.size();k++) {
		if((checklist.at(k)).rfind("E",0)==0) 
		checklist.erase(checklist.begin() + k);
		
	} //then I erase enemy nodes from my path and nodes are ready
	Node * newnode;
	Edge * newedge;
	vector<string>::iterator ptr;	
	Node * lastnode =NULL;
   for (ptr = checklist.begin(); ptr < checklist.end(); ptr++)	 {
	   	if(*ptr!="Mo")
	   	 newnode= new Node(*ptr);
	   	else  lastnode = new Node(*ptr);
   } // I am creating my nodes here and keep lastnode
   
 	city_plan.clear();
	city_plan.seekg(0);
	int stindex;
	int destindex;
	while(!city_plan.eof()){
			getline(city_plan, start,',');	
			getline(city_plan, dest,',');
			getline(city_plan, dist,'\n');
			dis=stoi(dist);
			
			vector<string>::iterator itr = find(checklist.begin(), checklist.end(), start);
			if(itr != checklist.end()){ // I added this controller ifs because of I do not want to use edges which contains E or close to E but they still in txt. 
										//So I can read from txt but since some nodes not in my nodes vector, there may be occured an error.
				stindex =distance(checklist.begin(), itr);
				itr = find(checklist.begin(), checklist.end(), dest);
				if(itr != checklist.end()){
						destindex =distance(checklist.begin(), itr);
						newedge = new Edge(nodes.at(stindex),nodes.at(destindex),dis);
				}
			}		
	} // here edges are reated
	vector<string>::iterator itr = find(checklist.begin(), checklist.end(), "Ma");
	stindex =distance(checklist.begin(), itr);
	nodes.at(stindex)->distance = 0; //set first distance as 0 to first node.

	mydijkstras();

    print(lastnode); //Since I design a vector from last to beginning, I give my last node.
    delete newedge;
    delete newnode;
	return 0;
}
