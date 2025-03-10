#include <iostream>
#include <stack>

struct node {
	char id;
	node* left;
	node* right;
	node(char ID) {id = ID, left = right = nullptr;};
};


std::stack <node*> st;
int gAntall, gAntall_NULL, gAntall_full, gHight;


void recursiv(node* current, const int start) {
	if (current) {
		if (current->left && current->right) { gAntall_full++; }
		gAntall++;
		recursiv(current->left, start+1);
		recursiv(current->right, start+1);
		if (start > gHight) { gHight = start; }
	} else { gAntall_NULL++; }
}



node* build_tree(std::string &expression) {
	for (char ch : expression) {
		if (ch >= '0' && ch <= '9') {
			st.push(new node(ch));
		} else if (ch == '*' || ch == '+') {
			node *current = new node(ch);
			current->right = st.top(); st.pop();
			current->left = st.top(); st.pop();
			st.push(current);
		}
	}
	return st.top();
}

int main(int argc, char *argv[]) {
	std::cout << "Write Expression PostOrder : ";
	std::string expression;
	std::getline(std::cin, expression);
	std::cout << std::endl;

	node *root = build_tree(expression); st.pop();

	recursiv(root, 1);

	std::cout << "Antall Noder : " << gAntall << std::endl;
	std::cout << "Antall nullptr : " << gAntall_NULL << std::endl;
	std::cout << "Antall fulle noder : " << gAntall_full << std::endl;
	std::cout << "Tree's Hight : " << gHight << std::endl;
	return 0;
}
