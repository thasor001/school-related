#include <iostream>
#include <stack>
#include <string>

std::stack <int> st;

void display(std::stack <int> Cst) {
	int len = Cst.size();
	std::stack <int> buffer;

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
	std::string expression;
	std::getline(std::cin, expression);
	std::cout << std::endl;
	int sum;

	for (char ch : expression) {
		if (ch >= '0' && ch <= '9') {
			st.push(ch - '0');
			display(st);
		} else if (ch == '*' || ch == '+') {
			int nr1 = st.top(); st.pop();
			int nr2 = st.top(); st.pop();
			switch(ch) {
				case '+': sum = nr1 + nr2; break;
				case '*': sum = nr1 * nr2; break;
				default: break;
			}
			st.push(sum);
			display(st);
		}
	}

	std::cout << "\n\nSum : " << sum << std::endl;
	return 0;
}
