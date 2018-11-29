#include "main.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;
using std::string;

class Node {
private:
	string name;
	int id;
	double rank;
	int outdegree = 0;
	Node* next = NULL;
	Node* temp = next;
public:
	Node(string n, int i) {
		name = n;
		id = i;
	}

	Node* getnext() {
		return next;
	}

	string getname() {
		return name;
	}

	int getid() {
		return id;
	}

	void setnext(Node n) {
		temp = next;
		outdegree++;
		rank = pow(outdegree, -1);
		if (temp == NULL) {
			Node *p = new Node(n.getname(), n.getid());
			next = p;
		}else
			temp->setnext(n);
	}

	int getdegree() {
		return outdegree;
	}

};

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
			id++;
		}
	}

	//table of URLs. Using an array
	string* data = new string[list.size()];

	//input of the table of URLs
	for (int i = 0; i < list.size(); i++) {
		data[i] = list[i].getname();
	}

	//sorts the table of URLs
	int z = sizeof(data) / sizeof(data[0]);
	sort(data, data + z);

	return 0;
}