#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iomanip>


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
	Node(string n, int i);

	Node* getnext();

	string getname();

	int getid();

	void setnext(Node n);

	vector<double> inter(double r, int V);

};