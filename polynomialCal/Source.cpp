#include <iostream>
#include <string>
#include <stack>
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

	void CreateTree(string s, int l) {
		node *x, *y, *z;
		x = y = z = NULL;
		for (int i = 0; i < l; i++) {
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

	// Input var x, y
	string inputVar(string s, char xy) {
		char var;
		cout << "Nhap vao bien " << xy << ": ";
		cin >> var;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == xy)
				s[i] = var;
		}
		return s;
	}

	string chooseVar(string s1, int check) {
		if (check == 1) {
			char varX = 'x';
			s1 = inputVar(s1, varX);
			char varY = 'y';
			s1 = inputVar(s1, varY);
		}
		if (check == 2) {
			char varX = 'x';
			s1 = inputVar(s1, varX);
		}
		if (check == 3) {
			char varY = 'y';
			s1 = inputVar(s1, varY);
		}
		return s1;
	}

	// kiem tra bieu thuc co bien hay khong
	int checkXY(string x) {
		int check, detect_x = 0, detect_y = 0;
		for (int i = 0; i < x.length(); i++) {
			if (x[i] == 'x')
				detect_x++;
			if (x[i] == 'y')
				detect_y++;
		}
		if (detect_x != 0 && detect_y != 0)
			check = 1;
		if (detect_y == 0)
			check = 2;
		if (detect_x == 0)
			check = 3;
		if (detect_x == 0 && detect_y == 0)
			check = 0;
		return check;
	}

	// chuyen doi infix --> postfix
	int prec(char c) {
		if (c == '^')
			return 3;
		else if (c == '/' || c == '*')
			return 2;
		else if (c == '+' || c == '-')
			return 1;
		else
			return -1;
	}

	string infixToPostfix(string s) {
		stack<char> st;
		string result;
		for (int i = 0; i < s.length(); i++) {
			char c = s[i];
			if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z') || (c >= '0'&&c <= '9'))
				result += c;

			else if (c == '(')
				st.push('(');
			else if (c == ')') {
				while (st.top() != '(') {
					result += st.top();
					st.pop();
				}
				st.pop();
			}

			else {
				while (!st.empty() && prec(s[i]) <= prec(st.top())) {
					if (c == '^'&&st.top() == '^')
						break;
					else {
						result += st.top();
						st.pop();
					}
				}
				st.push(c);
			}
		}
		while (!st.empty()) {
			result += st.top();
			st.pop();
		}
		return result;
	}

	// thuc hien tinh toan cay nhi phan 
	double atol(string s)
	{
		double x = 0, d = 1;
		int j = 0, k = 0;
		if (s[0] == '+' || s[0] == '-')
		{
			j = 1;
			if (s[0] == '-') k = 1;
		}
		for (int i = s.size() - 1; i >= j; i--)
		{
			switch (s[i])
			{
			case '0':x += 0 * d; break;
			case '1':x += 1 * d; break;
			case '2':x += 2 * d; break;
			case '3':x += 3 * d; break;
			case '4':x += 4 * d; break;
			case '5':x += 5 * d; break;
			case '6':x += 6 * d; break;
			case '7':x += 7 * d; break;
			case '8':x += 8 * d; break;
			case '9':x += 9 * d; break;
			}
			d *= 10;
		}
		if (k == 0)return x;
		return -x;
	}

	double Eval(node *t)
	{
		long x;
		if (t)
		{
			if (t->data == "+") return Eval(t->left) + Eval(t->right);
			else if (t->data == "-") return Eval(t->left) - Eval(t->right);
			else if (t->data == "*") return Eval(t->left)* Eval(t->right);
			else if (t->data == "/") return Eval(t->left) / Eval(t->right);
			else if (t->data == "^") return pow(Eval(t->left), Eval(t->right));
			else return atol(t->data); // chuyen string thanh so
		}
		return 0;
	}

	// main program


};

int main(){
	return 0;
}