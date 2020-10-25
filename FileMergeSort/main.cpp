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
		try
		{
			fms::FileMergeSort fileMergeSort(inputFileNames, "out.txt", fms::SortMode::increase, fms::SortType::string, 23);
			fileMergeSort.debug_getFileIO()->printFilesData();
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what();
		}

	}
	std::cin.get();

}