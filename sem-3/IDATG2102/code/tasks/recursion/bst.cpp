#include <iostream>

struct node {
	int id;
	node* left;
	node* right;
	node(int Id, node* l, node* r) {id = Id; left = l, right = r;}
};

node* gRoot = nullptr;
node* BST = nullptr;
const int MIN = 0,
		  MAX = 9999;

node* create_tree() {
	node *n3  = new node(3, nullptr, nullptr),
		*n30 = new node(30, nullptr, nullptr),
		*n10 = new node(10, nullptr, nullptr),
		*n57 = new node(57, n3, n30),
		*n27 = new node(27, nullptr, nullptr),
		*n13 = new node(13, nullptr, n10),
		*n31 = new node(31, n57, nullptr),
		*n34 = new node(34, nullptr, nullptr),
		*n7 = new node(7, n27, n13),
		*n35 = new node(35, nullptr, nullptr),
		*n82 = new node(82, nullptr, n31),
		*n5 = new node(5, n34, nullptr),
		*n33 = new node(33, n7, n35),
		*n11 = new node(11, n82, n5),
		*n17 = new node(17, n33, n11);
	return n17;
}

node* create_BST() {
	node *n1 = new node(1, nullptr, nullptr),
		 *n3 = new node(3, nullptr, nullptr),
		 *n2 = new node(2, n1, n3);
	return n2;

}

int finnMin(node* current);
int finnMax(node* current);
bool isBST(node* current);


int main(int agrv, char *argc[]) {
	gRoot = create_tree();
	BST = create_BST();

	std::cout << "Task A)" << "\nSmallest Integer in Tree : "
	<< finnMin(gRoot) << std::endl;

	std::cout << "\nTask B)" << "\nBiggest Integer in Tree : "
	<< finnMax(gRoot) << std::endl;

	std::cout << "\nTask C)" << "\nIs Tree BST : "
	<< isBST(gRoot) << std::endl;

	std::cout << "\nTask ?)" << "\nIs BST, BST : "
	<< isBST(BST) << std::endl;

	return 0;
}

int finnMin(node* current) {
	int min = MAX;
	if (current) {
		int left_node = finnMin(current->left);
		int right_node = finnMin(current->right);
		(left_node < right_node) ? min = left_node : min = right_node;
		if(current->id < min) { min = current->id; }
	}
	return min;
}


int finnMax(node* current) {
	int max = MIN;
	if (current) {
		int left_node = finnMax(current->left);
		int right_node = finnMax(current->right);

		(left_node >= right_node) ? max = left_node : max = right_node;
		if (current->id > max) { max = current->id; }
	}
	return max;
}

bool isBST(node* current) {
	bool pred = true;
	if (current) {
		int left_node = finnMax(current->left);
		bool left_pred = isBST(current->left);
		int right_node = finnMin(current->right);
		bool right_pred = isBST(current->right);

		if (left_node > current->id || !left_pred) { pred = false; }
		if (right_node < current->id || !right_pred) { pred = false; }
	}
	return pred;
}






