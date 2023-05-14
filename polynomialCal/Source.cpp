#include <iostream>
#include <string>
using namespace std;

class node {
public:
	string data;
	node *left;
	node *right;
	node *next;
public:

	//init node
	node(char data) {
		this->data = data;
		left = NULL;
		right = NULL;
		next = NULL;
	}
};

class Tree {
public:
	node *head;

	//init tree
	Tree() {
		head = NULL;
	}

	void PUSH(node *x) {
		if (head == NULL)
			head = x;
		else {
			x->next = head;
			head = x;
		}
	}

	node *POP() {
		node *p = head;
		head = head->next;
		return p;
	}

	node *CreateTree(string s, node *x, node *y, node *z) {
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '+' || s[i] == '*' || s[i] == '/' || s[i] == '^') {

			}
		}
	}

};

int main(){
	return 0;
}