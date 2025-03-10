#include <iostream> // Cout, Cin
#include <stack>    // Stack
#include <string>   // String
#include <cctype>   // Isdigit()

int main() {
	std::stack <int> st;
	std::string expression;

	std::cout << "Enter Postfix expression : ";
	std::getline(std::cin, expression);

	for (char ch : expression) {
		if (isdigit(ch))
			st.push(ch - '0');
		else {
			int val1 = st.top(); st.pop();
			int val2 = st.top(); st.pop();

			switch(ch) {
				case '+': st.push(val1 + val2); break;
				case '-': st.push(val1 - val2); break;
				case '*': st.push(val1 * val2); break;
				case '/': st.push(val1 / val2); break;
				default: std::cerr << "Error\n";
			}
		}
	}

	int solution = st.top(); st.pop();

	std::cout << "Final answer : " << solution << std::endl;

	return 0;
}

