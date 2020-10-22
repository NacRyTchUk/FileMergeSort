#include <iostream>


namespace fms {
	bool isBigger(char* a, char* b) {
		int lenA = strlen(a), lenB = strlen(b);
		return (lenA == lenB) ? (strcmp(a, b) > 0) : (lenA > lenB);
	}
}
