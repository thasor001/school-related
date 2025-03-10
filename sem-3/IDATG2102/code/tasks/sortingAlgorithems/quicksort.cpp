#include <iostream>

#define RESET  "\033[0m"
#define RED    "\033[91m"
#define BLUE   "\033[94m"
#define GREEN  "\033[32m"
#define YELLOW "\033[33m"

const int size = 10;

char array[size + 1];

void change(char & x, char & y) {
	int buffer = x;
	x = y;
	y = buffer;
}

int partisjon(char array[], const int left, const int right) {
	int i = left - 1;

	for (int j = left; j < right; j++)
		if (array[right] > array[j])
			change(array[j], array[++i]);
	change(array[right], array[++i]);
	return i;
}

void display(int x, int y, int z) {
	for (int i = 1; i <= size; i++) {
	if (i == x)
		std::cout << BLUE << array[i] << RESET << ' ';
	else if (i == y)
		std::cout << GREEN << array[i] << RESET << ' ';
	else if (i == z)
		std::cout << YELLOW << array[i] << RESET << ' ';
	else
		std::cout << array[i] << ' ';
	}
	std::cout << std::endl;
}

void quicksort(char array[], const int left, const int right) {
	if (right > left) {
		int index = partisjon(array, left, right);
		display(index, left-1, right);
		quicksort(array, left, index - 1);
		quicksort(array, index + 1, right);
	}
}

int main(int argc, char * argv[]) {
	array[0]  = '!';
	array[1]  = 'L';
	array[2]  = 'I';
	array[3]  = 'G';
	array[4]  = 'A';
	array[5]  = 'M';
	array[6]  = 'E';
	array[7]  = 'S';
	array[8]  = 'T';
	array[9]  = 'E';
	array[10] = 'R';


	quicksort(array, 1, size);

	std::cout << "\n\nFinished Array: \n";
	for (int i = 1; i <= size; i++)
		std::cout << array[i] << ' ';
	std::cout << std::endl;

	return 0;
}
