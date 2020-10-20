/*
AOE Task Manager
Project #4
CIS 279
Haoran Zhi
2019/5/16

Purpose: the porpose of this program is to slove graph probelms and 
finding the longest path in a graph
*/
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

//create a structure called Pairs it contains the node number
// the vertex the edge is going to, and the duration of the activity
struct Pairs{
    int node;
	int vertex;
	int dur;
};
//create all the globle arrays that is used in this program
vector<Pairs> Headnodes[360];
vector<Pairs> BackupList[360];
int ee[360];
int le[360];
int Incount[360], Outcount[360];
bool visited[360];
bool visited2[360];
stack<vector<Pairs>> s;
stack<vector<Pairs>> g;






//The function topologicalsort takes in the number of vertex, the node number to 
//start sorting and a array to mark which node had been visited
void topologicalsort(int n, int v, bool visit[]){
	//set the current node to visited
	visit[v] = true;
for(int i = 0; i < n; i++){
	//the vector inside the node v
	vector<Pairs> t = Headnodes[v];
	//loop through the vector 
	for(int j = 0; j < t.size(); j++){
		//apply recursion if the next node is not visit
		if(!visit[t[j].vertex]){
			topologicalsort(n, t[j].vertex, visit);
		}
	}
}
	//push the vector into the stack
	s.push(Headnodes[v]);

}





//This function is used to compute the latest time an event 
//would occur and it is the same as the first topologicalsort
void topologicalsort2(int n, int v){
	visited2[v] = true;
	//set the current node to visited
for(int i = 0; i < n; i++){
	vector<Pairs> t = BackupList[v];
	//loop through the vector 
	for(int j = 0; j < t.size(); j++){
		if(!visited2[t[j].vertex]){
			//apply recursion if the next node is not visit
			topologicalsort2(n, t[j].vertex);
		}
	}
}
//push the vector into the stack
	g.push(BackupList[v]);


}






//The insert function takes in three ingeters as input and puts 
//a pairs object into the adjacency list
void insert(int nodeNumber, int ver, int Dur){
	Pairs n1;
	n1.node = nodeNumber;
	n1.vertex = ver;
	n1.dur = Dur;
	Pairs n2;
	n2.node = ver;
	n2.vertex = nodeNumber;
	n2.dur = Dur;
	Headnodes[nodeNumber].push_back(n1);
	BackupList[ver].push_back(n2);
}






//The Latest Time function takes in an integer as input and 
//compute the latest time for each event to occur
void LatestTime(int vNum){
	//loop through the nodes
	for (int i = 0; i < vNum; i++){
		//initialize those two array for futher computation
		visited2[i] = false;
		le[i] = ee[vNum-1];
		//finds a node with 0 successors
		if(Outcount[i] == 0){
			// run topologicalsort with the node
			topologicalsort2(vNum, i);
		}
	}
	//loop until stack is empty
	while(!g.empty()){
		//pop out the top of the stack
		vector<Pairs> temp = g.top();
		g.pop();
		//loop through its components
		for(int j = 0; j < temp.size(); j++){
			int k = temp[j].vertex;
			int f = temp[j].node;
			//update the latest time
			if(le[k] > (le[f]-temp[j].dur))
				le[k] = le[f]-temp[j].dur;

		}
	}
	//print out the result
	cout << "The Lalest time that each event may occur is: " << endl;
	for(int i = 0; i < vNum; i++){
	    cout << "Event " << i << " : " << le[i] << " unit time" << endl;
	}
}










//The EarliestTime function takes in an integer as input and 
//compute the earliest time for each event to occur
void EarliestTime(int vertexN){
	int top = -1;
	//initialize those arrays for futher computation
	for(int i = 0; i < vertexN; i++){
		visited[i] = false;
	    ee[i] = 0;
	}
	
	//find a node with 0 predecessor to start
	for(int i = 0; i < vertexN; i++){
		if (Incount[i] == 0){
		    cout << "Find it"<< endl;
		    //compute the topological order
			topologicalsort(vertexN, i, visited);
			top = i;
		}
	}
	//stop the program if the graph is not a DAG
	if (top == -1){
	    cout << "Network has a cycle.";
	    return;
	}
	//loop until stack is empty
	while(!s.empty()){
		//pop out the top of the stack
	        vector<Pairs> temp = s.top();
	        s.pop();
	        //loop through its components
	       for (int j = 0; j < temp.size(); j++){
	           int k = temp[j].vertex;
	           int w = temp[j].node;
	           //update the earliest time
	           if (ee[k] < (ee[w]+temp[j].dur))
			        ee[k] = ee[w]+temp[j].dur;
			    Incount[k]--;
			    
	        }
	        
	    }
	    //print out the result
	cout << "The Earlest time that each event may occur is: " << endl;
	for(int i = 0; i < vertexN; i++){
	    cout << "Event " << i << " : " << ee[i] << " unit time" << endl;
	}


}


//this is the main function 
int main(){
	//create two integer to store the number of vertex and number of activities
	int V;
	int E;
	//ask the user to how many vertex is in this graph
	cout << "PLease enter the number of verteses: "<< endl;
	cin >> V;
	//create two array used for counting the number of edges going in and out
	
		//initialize them all to 0
	for (int i = 0; i < V; i++){
	    Headnodes[i] = {};
	    BackupList[i] = {};
		Incount[i] = Outcount[i] = 0;
	}
	//prompt the user to enter the number of edges
	cout << "Please enter the number of egdes: " << endl;
	cin >> E;
	//loop through the number of connections and create a Adjacency list
	int A_Order[E];
	for (int i = 0; i < E; i++){
		int N, ver, D, A;

		cout << "Enter the node number: " << endl;
		cin >> N;
		Outcount[N]+=1;
		cout << "Enter the vertex to connect to: " << endl;
		cin >> ver;
		Incount[ver]+=1;
		cout << "Enter the duration of the activity: " << endl;
		cin >> D;
		cout << "Enter the order of this activity: " << endl;
		cin >> A;
		A_Order[i] = A;// record of the name of the activity
		insert(N, ver, D);

	}
//compute the earliest time 
EarliestTime(V);

//if there isn't a loop 
if(ee[V-1] != 0){
	//compute the latest time 
    LatestTime(V);
    //compute the critical events
    cout << "the critical Events are : " << endl;;
    for (int i = 0; i < V; i++){
        if((ee[i]-le[i]) == 0){
            cout << "Event " << i << endl;
        }
    }
    cout << "The longest path in this activity network has a duration of: " << ee[V-1] << "unit time";
}

}