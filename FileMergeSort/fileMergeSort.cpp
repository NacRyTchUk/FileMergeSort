#include <iostream>
#include "SortParameters.h"

namespace fms {
	

	bool isFileHasRightFormat(const char* fileName, std::string format) {
		int iter{ (int)strlen(fileName) };
		for (int i = format.size() - 1; i >= 0; i--)
			if (fileName[--iter] != format[i])
				return false;
		return true;
	}

	bool isBigger(const char* a, const char* b, SortType sortType) {
		int lenA = strlen(a), lenB = strlen(b);
		//if (lenB == 0) return false;
		return (lenA == lenB) || (sortType == SortType::string) ? (strcmp(a, b) > 0) : (lenA > lenB);
	}

	int stringToSizeTryParse(char * str) {
		try
		{
			return std::atoi(str);
		}
		catch (const std::exception&)
		{
			return -1;
		}
	}

	namespace FileMergeSort {

	}
}
