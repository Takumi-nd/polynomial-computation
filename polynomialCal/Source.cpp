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
		char after = ' ';
		if (s[i] == '-' && s[i + 1] == '(') {
			after = s[i + 2]; // luu ky tu sau ngoac
			for (j; s[j] != ')'; j++) {
				if (s[j] == '+') {
					s[j] = '-';
					continue;
				}
				if (s[j] == '-')
					s[j] = '+';
				count = j;
			}
			s.erase(s.begin() + i + 1); // xoa dau '('
			s.erase(s.begin() + count); //xoa dau ')'
			if (after == '-') {
				s.erase(s.begin() + i);
				s.erase(s.begin() + i);
				if (i != 0 && s[i - 1] != '*' && s[i - 1] != '/' && s[i - 1] != '^')
					s.insert(s.begin() + i, '+'); //neu dau tru khong o dau chuoi, truoc do la *,/,^ thi thay -- thanh +
			}
			else { // neu sau dau ngoac khong phai dau tru
				s.insert(s.begin() + i, '0');
				if (i != 0 && s[i - 1] != '*' && s[i - 1] != '/' && s[i - 1] != '^')
					s.insert(s.begin() + i, '+');
			}
		}
		if (s[i] == '(' && s[i + 1] == '-') // vd: b+(-a)
			s.insert(s.begin() + i + 1, '0');
		return s;
	}

};

int main(){
	return 0;
}