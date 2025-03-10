#include <iostream>
#include <stack>
#include <string>


struct node {
	char id;
	bool seen;
	node* right;
	node* left;
	node(char Id) { id = Id; seen = false; right = left = nullptr; }
};


std::stack <node*> st;


node* build_tree(std::string &expression) {
	for (char ch : expression) {
		std::cout << ch << ' ';
		if (ch >= '0' && ch <= '9') {
			st.push(new node(ch));
		} else if (ch == '*' || ch =='+') {
			node *current = new node(ch);
			current->right = st.top(); st.pop();
			current->left = st.top(); st.pop();
			st.push(current);
		}
	}
	return st.top();
}


void post(node *root) {
	std::stack <node*> noder; noder.push(root);
	std::cout << std::endl;

	while (noder.size() != 0) {
		if (noder.top()->left != nullptr && !noder.top()->left->seen)
			noder.push(noder.top()->left);
		else if (noder.top()->right != nullptr && !noder.top()->right->seen)
			noder.push(noder.top()->right);
		else {
			std::cout << noder.top()->id << ' ';
			noder.top()->seen = true;
			noder.pop();
		}
	}
	std::cout << std::endl;
}


void inn(node *root) {
	std::stack <node*> noder; noder.push(root);
	std::cout << std::endl;

	while (noder.size() != 0) {
		
	}

	std::cout << std::endl;
}



int main() {
	std::cout << "Write Expression PostOrder : ";
	std::string expression;
	std::getline(std::cin, expression);
	std::cout << std::endl;

	node *root = build_tree(expression); st.pop();
	return 0;
}

