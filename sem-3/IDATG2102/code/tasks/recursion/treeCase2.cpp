#include <iostream>

struct node {
	int verdi;
    char id;
    int sum;
    node* left;
    node* right;
    node* parent;
};

int gNumber = 0;

node* generate(const int depth, const int probability) {
    node* rot = nullptr;                   //  Peker til det som returneres.
                                           //  NB: Initieres til 'nullptr'!
    if (depth > 0) {                       //  Kan fortsatt legge til et nivå:
        if (rand() % 100 < probability) {  //  Trukket tall i rett intervall:
            rot = new node;                //  Lager en ny node.
            rot->left = generate(depth-1, probability); //Lager evt v.subtre.
                                           //  4x linjer med "besok":
            rot->verdi = ++gNumber;             //  Legger inn egen verdi.
            rot->id = static_cast <char> ('A'-1+gNumber);  //  Legger inn ID.
            rot->sum = 0;                       //  Nullstiller egen sum.
            rot->parent = nullptr;            //  Nullstiller egen forelder.

            rot->right = generate(depth-1, probability); //Lager evt h.subtre.
        }
    }
    return rot;                     //  Returnerer generert tre eller nullptr.
}

node* gRoot = nullptr;

void traverse(node* current) {
	if (current) {
		traverse(current->left);
		std::cout << "ID: " << current->id << '\n';
		traverse(current->right);
	}
}

int main(int argc, char * argv[]) {
	gRoot = generate(5, 80);
	traverse(gRoot);

	return 0;
}
