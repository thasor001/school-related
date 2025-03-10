#include <iostream>
#include <stack>
#include <string>

std::stack <char> st;

void display(std::stack <char> Cst) {
	int len = Cst.size();
	std::stack <char> buffer;

	for (int i = 0; i < len; i++) {
		buffer.push(Cst.top());
		Cst.pop();
	}

	if (len == 0)
		std::cout << '|';

	for (int i = 0; i < len; i++) {
		std::cout << buffer.top(); buffer.pop();
		std::cout << ' ';
	}
	std::cout << '\n';
}

int main() {

	std::string rpn = "";
	std::string expression;
	std::getline(std::cin, expression);
	std::cout << std::endl << '|' << '\n';

	for (char ch : expression) {
		if (ch >= '0' && ch <= '9') {
			rpn += ch;
			rpn += ' ';
		}
		else if (ch == ' ' || ch == '(') {}
		else if (ch == ')') {
			rpn += st.top();
			rpn += ' ';
			st.pop();
			display(st);
		}
		else if (ch == '*' || ch == '+') {
			st.push(ch);
			display(st);
		}
	}

	std::cout << '\n' << rpn << '\n';

	return 0;
}
