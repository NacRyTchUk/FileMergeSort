#include <iostream>

bool isBigger(char* a, char* b) {
	int lenA = strlen(a), lenB = strlen(b);
	return (lenA == lenB) ? (strcmp(a, b) > 0) : (lenA > lenB);
}


int main(int argc, char * argv[]) {
	if (argc > 2)
		std::cout << isBigger(argv[1], argv[2]) << std::endl;
}