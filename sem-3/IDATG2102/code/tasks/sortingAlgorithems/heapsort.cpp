#include <iostream>
#include <string>

#define RESET "\033[0m"
#define RED   "\033[91m"
#define BLUE  "\033[94m"
#define GREEN "\033[32m"

const int size = 10;

char array[size + 1];


void display(char array[]) {
	std::cout   << "	       " << array[1] <<  '\n'
				<< "	     / "              "  \\" << '\n'
				<< "	   " << array[2] << "       " << array[3] << '\n'
				<< "	 /  \\     /  \\\n"
				<< "       " << array[4] << "     " << array[5]
				<< "   " << array[6] << "     " << array[7] << '\n'
				<< "     /  \\   /\n"
				<< "   " << array[8] << "     " << array[9] << " " << array[10];


	std::cout << std::endl;
}

void display2(char array[], const int n) {
	for (int i = 1; i <= n; i++) {
		std::cout << array[i] << ' ';
	}
	std::cout << std::endl;
}

void displayChange(char array[], const int x, const int y, const std::string & COLOR, const int n) {
	for (int i = 1; i <= size; i++) {
		if (i == x || i == y) {
			std::cout << COLOR << array[i] << RESET << ' ';
		} else if (i >= n) {
			std::cout << GREEN << array[i] << RESET << ' ';
		} else {
			std::cout << array[i] << ' ';
		}
	}
	std::cout << std::endl;
}


void change(char & x, char & y) {
	char buffer = x;
	x = y;
	y = buffer;
}

void heapSort(char array[], int n) {
	// a g x z f f f y h c
	int i;

	while (n > 1) {
		for(i = n; i > 1; i--) {
			std::cout << "\nChecking " << BLUE << "BLUE" << RESET << " : ";
			displayChange(array, i, i-1, BLUE, n);
			if (array[i] > array[i-1]) {
				std::cout << "\nChecking " << RED << "RED" << RESET << "  : ";
				displayChange(array, i, i-1, RED, n);
				change(array[i], array[i-1]);
			}
		}

		std::cout << "\nChanging first and last element : ";
		displayChange(array, 1, n, RED, size);
		std::cout << "N = " << n << std::endl;
		change(array[1], array[n]);
		n--;

	}
}

int main(int argc, char * argv[]) {
	array[0] = 'a';
	array[1] = 'A';
	array[2] = 'G';
	array[3] = 'X';
	array[4] = 'Z';
	array[5] = 'F';
	array[6] = 'F';
	array[7] = 'F';
	array[8] = 'Y';
	array[9] = 'H';
	array[10]= 'A';

	std::cout << "Heap sort :\n";

	std::cout << "\nBefore sort : \n";
	display(array);

	heapSort(array, size);

	std::cout << "\nAfter Sort:\n";
	display2(array, size);

	std::cout << std::endl;

	display(array);

	return 0;
}
