#include <iostream>

const int N = 4;

int solutions = 0;
int number = 0;

void display(int array[]) {
    for (int i = 0; i < N; i++) { std::cout << array[i] << ' '; }
    std::cout << std::endl;
}

void solver(int array[]) {
	display(array);
	number++;
	for (int i = 0; i < N; i++) {
		if (array[i] == array[i+1]-1 || array[i] == array[i+1]+1) {
			return;
		}
	}
	solutions++;
}

void permute(int array[], const int i, const int n) {
	if (i < n) {
		int buffer;
		for (int j = i + 1; j < n + 1; j++) {
			buffer = array[i];
			array[i] = array[n];
			array[n] = buffer;

			solver(array);

			permute(array, i+1, n);
		}
		permute(array, i+1, n);
	}
}

int main(int argc, char* argv[]) {
	int array[N];

	for (int i = 0; i < N; i++) {
		array[i] = i+1;
	}

	permute(array, 0, N-1);

	// To check if the Array truly is back at the start:
	std::cout << "\n\nArray should be incrementing by 1 from 1 to N : " << std::endl;
	display(array);

	std::cout << "\nNumber of different combinations : " << number << std::endl;

}
