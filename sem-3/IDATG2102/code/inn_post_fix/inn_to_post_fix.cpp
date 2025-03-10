#include <iostream>
#include <string>
#include <stack>

int main() {
	std::stack <char> Operators;
	std::string rpn;

	std::string buffer;
	std::getline(std::cin, rpn);

	for (char ch : buffer) {
		if ((ch >= '0' && ch <= '9') || ch == ' ') {
			rpn.push_back(ch);
		} else if (ch == ')') {
			rpn.push_back(Operators.top());
			Operators.pop();
		} else if (ch == '*' || ch == '/' || ch == '-' || ch == '+'){
			Operators.push(ch);
		}
	}


	std::cout << rpn << '\n';
	return 0;
}






