#include <cstdlib>

struct node {
	int id;
	node* left;
	node* right;
	node(const int ID, node* l, node* r)
		{ id = ID; left = l; right = r; }
};

node* generate(const int depth, const int probability) {
	node *rot = nullptr;

	if (depth > 0 && rand()%100 < probability) {
		rot = new node(0, nullptr, nullptr);
		


	}

	return rot;
}
