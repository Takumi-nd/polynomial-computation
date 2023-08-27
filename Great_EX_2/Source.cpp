#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <queue>
using namespace std;

struct node {
	string data;
	node *left;
	node *right;
	node *next; //stack
};
typedef node* tree;
node *head = NULL;

node *newNode(char data){
	node *p = new node;
	p->data = data;
	p->left = NULL;
	p->right = NULL;
	p->next = NULL;
	return p;
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


void CreatTree(string s, int l) {
    node *x, *y, *z;
    x = y = z = NULL;
	for (int i = 0; i < l; i++) {
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^') {
			z = newNode(s[i]);
			x = POP(); //ra truoc vao right
			y = POP(); //ra truoc vao left
			z->left = y;
			z->right = x;
			PUSH(z);
		}
		else {
			z = newNode(s[i]);
			PUSH(z);
		}
	}
}

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

double Eval(tree t)
{
	//long x;
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


int checkXY(string x) {
	int check, detect_x=0, detect_y=0;
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

string InputVar(string s, char x_y);

string defVar(string s1, int check) {
	if (check == 1) {
		char varX = 'x';
		s1 = InputVar(s1, varX);
		char varY = 'y';
		s1 = InputVar(s1, varY);
	}
	if (check == 2) {
		char varX = 'x';
		s1 = InputVar(s1, varX);
	}
	if (check == 3) {
		char varY = 'y';
		s1 = InputVar(s1, varY);
	}
	return s1;
}

string InputVar(string s, char x_y) {
	char var;
	cout << "Nhap vao bien " << x_y << ": " ;
	cin >> var;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == x_y)
			s[i] = var;
	}
	return s;
}

string stringHandling(string s, int i) {
		int j = i+1, cout;
		if (s[i] == '-' && s[i+1] == '(') {
			char after = s[i + 2]; // luu ky tu sau dau ngoac
			for (j; s[j] != ')';j++) {
				if (s[j] == '+') {
					s[j] = '-';
					continue;
				}
				if (s[j] == '-') {
					s[j] = '+';
				}
				cout = j;
			}
			s.erase(s.begin() + i+1); // xoa dau '('
			s.erase(s.begin() + cout); // xoa dau ')'
			if (after == '-') { // neu sau dau ngoac la - thi xoa ca hai dau tru
				s.erase(s.begin() + i);
				s.erase(s.begin() + i);
				if (i != 0 && s[i - 1] != '*' && s[i - 1] != '/' && s[i - 1] != '^')
					s.insert(s.begin() + i,'+'); //neu dau tru khong o dau chuoi, truoc do la *,/,^ thi thay -- thanh +
			}
			else { // neu sau dau ngoac khong phai dau tru
				s.insert(s.begin() + i,'0');
				if(i!=0 && s[i-1] != '*' && s[i-1] !='/' && s[i-1] != '^')
					s.insert(s.begin() + i, '+');
			}
		}
		if (s[i] == '(' && s[i + 1] == '-') { // vd: b+(-a)
			s.insert(s.begin() + i + 1, '0');
		}
	return s;
}

int main() {
	string s, s1;
	int select;
	int check;
	int i;

	cout << "*Da thuc chi co the chua: " << endl;
	cout << "\t" << "- Hang so la cac so nguyen co mot chu so: 0 --> 9" << endl;
	cout << "\t" << "- Toan tu: *,/,+,-,^ va dau '(' ; ')'" << endl;
	cout << "\t" << "- Cac bien x va y " << endl;
	cout << "*Viet so am theo dang: (-a)" << endl;
	cout << "*Nhap ro rang cac toan tu" << endl;
	cout << "---------------------------" << endl;

	while (1) {
		cout << "-->Nhap 1 de tiep tuc, Nhap 0 de thoat: "; cin >> select; cout << endl;
		if (select == 0) {
			cout << "Thoat chuong trinh" << endl;
			exit(1);
		}
		cout << "Moi nhap da thuc: ";
		cin >> s;// nhap vao da thuc dang infix

		for (i = 0; i < s.length(); i++) {
			s = stringHandling(s, i); //Xu ly chuoi
		}

		s1 = infixToPostfix(s);//chuyen infix thanh postfix

		check = checkXY(s1); // Kiem tra da thuc co bien x hay y hay khong
		if(check != 0)
            s1 = defVar(s1, check);// nhap gia tri cho bien

		CreatTree(s1, s1.length()); // To chuc cay nhi phan da thuc
		cout << "Ket qua cua da thuc tren la: ";
		cout << Eval(head); // Thuc hien tinh toan cay va in ra ket qua
		cout << endl << endl;
	}
	return 0;
}
