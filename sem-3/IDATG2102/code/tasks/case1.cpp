#include <iostream>

int main() {
	int i = 0, sum;

	while(true) {
		i+=2;
		sum = 0;
		if (((i % 10) == 6) || ((i % 100) == 28)) {
			int end = i/2;
			for (int j = 1; j <= end; j++) {
				if (i % j == 0) {
					sum += j;
				}
			}
		}
		std::cout << sum << " ";
		if (sum == i) { std::cout << sum << " "; }
	}

	return 0;
}
