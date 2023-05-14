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
public:
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
				z = new node(s[i]);
				x = POP();
				y = POP();
				z->left = y;
				z->right = x;
				PUSH(z);
			}
			else {
				z = new node(s[i]);
				PUSH(z);
			}
		}
	}
};

class Cal {
public:
	string dataIn;
public:

	void inputPol() {
		cout << "Moi nhap vao da thuc: ";
		cin.ignore();
		getline(cin, dataIn);
	}

	string dataPreProcess(string s, int i) {
		int j = i + 1, count;
		if (s[i] == '-' && s[i + 1] == '(') {
			char after = s[i + 2]; // luu ky tu sau ngoac
			for (j; s[j] != ')'; j++) {

			}
		}
	}

};

int main(){
	return 0;
}