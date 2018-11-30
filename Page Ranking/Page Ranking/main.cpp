#include "main.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;
using std::string;

Node::Node(string n, int i) {
	name = n;
	id = i;
}

Node* Node::getnext() {
	return next;
}

string Node::getname() {
	return name;
}

int Node::getid() {
	return id;
}

void Node::setnext(Node n) {
	temp = next;
	outdegree++;
	rank = pow(outdegree, -1);
	if (temp == NULL) {
		Node *p = new Node(n.getname(), n.getid());
		next = p;
	}
	else
		temp->setnext(n);
}

vector<double> Node::inter(double r, int V) {

	/*this method determines the number of pages linked to this node and returns
	the result of the multiplication between this node's rank and the corrsponding
	value on matrix r(t)
	*/

	temp = next;
	vector <double> results(V);
	double num = rank * r;

	//every id located returns the value num on that index of r(t)
	while (temp != NULL) {
		results[temp->getid() - 1] = num;
		temp = temp->getnext();
	}

	return results;
}

int main() {

	string input;
	int lines;
	int iteration;
	string l = "";
	int index = 0;
	int id = 1;;

	//get the FIRST line that contains the number of lines and the number of iterations
	getline(cin, input);
	const char *lin = input.c_str();

	//this block finds the number of lines
	while (isdigit(lin[index])) {
		l = l + lin[index];
		index++;
	}
	stringstream geek(l);
	geek >> lines;
	l = "";

	//skip whitespace
	while (!isdigit(lin[index]))
		index++;

	//this block finds the number of iterations
	while (index != input.length() + 1) {
		l = l + lin[index];
		index++;
	}
	stringstream gess(l);
	gess >> iteration;

	//graph representation: adjacency list
	vector<Node> list;
	

	//the input of every line and creation of nodes
	for (int i = 0; i < lines; i++) {

		//this will keep track of the name of the node
		l = "";

		//x and y are going to keep track wether or not the nodes already exist
		bool x = true;
		bool y = true;

		//j and r are going to keep track of the index in which the nodes are located in vector<Node> list
		int j;
		int r;

		//the line of text
		index = 0;
		getline(cin, input);
		const char *line = input.c_str();

		//finds the "from" node. checks until a whitespace is found
		while (line[index] != ' ' && line[index] != '/t') {
			l = l + line[index];
			index++;
		}
		
		//checks if exists in list already
		for (j = 0; j < list.size(); j++) {
			if (list[j].getname() == l) {
				x = false;
				break;
			}
		}

		//creates a new node if it does not exist
		if (x) {
			Node p(l, id);
			list.push_back(p);
			id++;
		}
		l = "";

		//skips whitespace until finding more text
		while (line[index] == ' ' || line[index] == '/t') 
			index++;
		
		//finds the "to" node. checks until end is reached
		while (index != input.length()) {
			l = l + line[index];
			index++;
		}
			
		//checks if exists in list already
		for (r = 0; r < list.size(); r++) {
			if (list[r].getname() == l) {
				y = false;
				break;
			}
		}

		//creates a new node IF it does not exist and points the "from" node to it. else it points the "from" node to this node
		if (y) {
			Node p(l, id);
			list.push_back(p);
			id++;
			list[j].setnext(p);
		}
		else {
			list[j].setnext(list[r]);
		}
	}

	int V = list.size();

	//table of URLs. Using an array
	vector<string> data(V);

	//input of the table of URLs
	for (int i = 0; i < V; i++) {
		data[i] = list[i].getname();
	}

	sort(data.begin(), data.end());

	//in order to calculate the iterations, we use the formula: r(t+1) = M*r(t)
	//M is a "matrix" of the links between the web pages. it contains 0 where there is no link and a number >0 if it does
	//Since we are using an adjacency list, we are going to replicate the matrix multiplication using the nodes

	//we initialize the entries of r(t) to 1/V where V is the number of pages
	vector <double> r;
	for (int i = 0; i < V; i++) 
		r.push_back(pow(V, -1));

	//this block of code adds every single instance of rows with other columns
	for (int j = 0; j < iteration-1; j++) {
		vector <double> sum(V);
		for (int i = 0; i < V; i++) {
			vector <double> medium = list[i].inter(r[i],V);
			for (int w = 0; w < V; w++)
				sum[w] = sum[w] + medium[w];
		}
		r = sum;
	}



	//set doubles to only 2 decimals
	cout << setprecision(2) << fixed << "\n";


	//this prints the rank in alphabetical order
	for (int i = 0; i < V; i++) 
		for (int j = 0; j < V; j++) 
			if (data[i] == list[j].getname())
				cout << data[i] << " " << r[j] << "\n";
		
	


	return 0;
}