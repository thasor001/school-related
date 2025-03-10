#include <iostream>

struct node {
	char id;
	node* naboer[10];
	int antNaboer;
	bool besokt;
	node(const char ch, const int nr) { id = ch; antNaboer = nr; }
	node() {}
};

node* gRoot;

node* settUp() {
	node* n1 = new node; n1->id = 'A'; n1->besokt = false;
	node* n2 = new node; n2->id = 'B'; n2->besokt = false;
	node* n3 = new node; n3->id = 'C'; n3->besokt = false;
	node* n4 = new node; n4->id = 'D'; n4->besokt = false;
	node* n5 = new node; n5->id = 'E'; n5->besokt = false;

	n1->naboer[0] = n2; n1->naboer[1] = n3; n1->antNaboer = 2;
	n2->naboer[0] = n4; n2->antNaboer = 1;
	n3->naboer[0] = n4; n3->naboer[1] = n5; n3->antNaboer = 2;
	n4->naboer[0] = n5; n4->antNaboer = 1;
	n5->antNaboer = 0;

	return n1;
}

node* kopier(node* Node) {
	node* kopi = new node(Node->id + 32, Node->antNaboer);
	for (int i = 0; i < Node->antNaboer; i++) {
		kopi->naboer[i] = kopier(Node->naboer[i]);
	}
	return kopi;
}


void display(node* current) {
	std::cout << "ID : " << current->id << "\n";
	for (int i = 0; i < current->antNaboer; i++)
		display(current->naboer[i]);
}


void brettUt(node* current) {
	current->besokt = true;
	for (int i = 0; i < current->antNaboer; i++) {
		if (current->naboer[i]->besokt)
			current->naboer[i] = kopier(current->naboer[i]);
		brettUt(current->naboer[i]);
	}
}

int main() {
	gRoot = settUp();

	display(gRoot);

	brettUt(gRoot);

	std::cout << "\n\n";

	display(gRoot);

	return 0;
}
