#include <iostream>
#include <ctime>
#include <vector>
#include "FileMergeSort.h"


int main(int argc, char* argv[]) {
	if (argc < 3)
		return 1;

	std::vector<std::string> inputFileNames;
	for (int i = 1; i < argc; i++)
		inputFileNames.push_back(argv[i]);
	
	{
		fms::FileMergeSort fileMergeSort(inputFileNames, "out.txt", 1000 * 1000 * 50);

		fileMergeSort.debug_getFileIO()->printFilesData();
	}
	std::cin.get();

}