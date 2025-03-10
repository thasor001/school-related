#include <stdio.h>
#include <string.h>

int main() {

	char texten[100] = "hello World!";
	char vokal[12] = "aeiouyAEIOUY";

	// strchr <- tar inn en array med char, og en char (c). strchr(array, char);
	// Den sjekker om det finnes en c i char arrayen. hvis! ikke print.

	printf("%ld\n", sizeof(texten));
	// Går gjennom alle bokstevene i tekst
	for (int i = 0; i < (sizeof(texten) * sizeof(teksten[0])); i++) {
		// Bare print når teksten[i] IKKE er en del av vokal array.
		if (!strchr(vokal, texten[i]))
			printf("%c ", texten[i]);
	}

	printf("\n");
	return 0;
}
