// File Created by User: "thar" on date: "2024-09-26 14:56:00"
// File name: "shellsort.cpp"
#include <iostream>
#include <string>

const int size = 10;

void display(const char array[]) {
	for (int i = 1; i <= size; i++) {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
}


void shellsort(char array[], const int size) {
	int i, j, h;
	char buffer;

	for (h = 1;  h <= size/9; h = 3 * h + 1);

	while (h > 0) {
		for (i = h + 1; i <= size; i++) {
			j = i;
			buffer = array[i];
			std::cout << "\nBuffer = " << buffer << '\n';

			while(j > h && array[j-h] > buffer) {
				array[j] = array[j-h];
				std::cout << "Bytter : " << array[j] << " Med : "
				<< array[j-h] << std::endl;
				j -= h;
			}

			array[j] = buffer;
			std::cout << "\nh : " << h << " | i : " << i << '\n';
			display(array); // Displaying array.
		}
		h /= 3;
	}
}


int main(int argc, char* argv[]) {
	char array[size + 1];

	array[0] = '!';
	array[1] = 'S';
	array[2] = 'T';
	array[3] = 'R';
	array[4] = 'O';
	array[5] = 'G';
	array[6] = 'A';
	array[7] = 'N';
	array[8] = 'O';
	array[9] = 'F';
	array[10] = 'F';

	std::cout << "Shell Sort : \n";

	std::cout << "Before : ";
	display(array);

	shellsort(array, size);

	std::cout << "\nAfter : ";
	display(array);
	std::cout << std::endl;

    return 0;
}
