#include <iostream>
#include <vector>
#include <algorithm>

struct node {
	int id;
	node* left;
	node* right;
	node(const int ID, node* l, node* r)
		{ id = ID; left = l; right = r; }
};

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

node* gRoot = nullptr;

void hoyregren() {
	std::cout << "Road to the Right most Leaf Node: ";
	node *current = gRoot;

	while(current) {
		std::cout << current->id << ' ';
		current = (current->right) ? current->right : current->left;
	}
	std::cout << std::endl;
}


void gren(node* leaf) {
	node* current = gRoot;
	while (current) {
		std::cout << current->id << ' ';
		current = (leaf->id < current->id) ? current->left : current->right;
	}

	std::cout << std::endl;
}

std::vector <int> gNodes;
int antall = 0;
int gNivaa = 0;

void travers(node* current) {
	if (current) {
		travers(current->left);
		travers(current->right);
		gNodes.push_back(current->id);
	}
}

void to_bst(node* current) {
	if (current) {
		gNivaa++;
		to_bst(current->left);
		current->id = gNodes[antall++];
		to_bst(current->right);
		std::cout << current->id << "  Nivaa : " << gNivaa << std::endl;
		gNivaa--;
	}
}

void grener(node* current) {
	if (current) {
		grener(current->left);
		grener(current->right);
		if (!current->left && !current->right) {
			gren(current);
			return;
		}
	}
}


int main(int argc, char *argv[]) {
	gRoot = create_tree();
	travers(gRoot); 							// Put All nodes into an array.
	std::sort(gNodes.begin() ,gNodes.end());	// Sort Vector containing all node ID's
	std::cout << std::endl;
	to_bst(gRoot);							  	// Make the Tree into a BST
	std::cout << std::endl;

	hoyregren();
	grener(gRoot);

	return 0;
}
