#include <iostream>
#include <ctime>
#include <vector>
#include <set>
#include "FileMergeSort.h"




int main(int argc, char* argv[]) {
		try
		{
			std::set<std::string> param;
			for (int i = 1; i < argc; i++)
				param.insert(argv[i]);

			if (param.size() < 3)
				throw std::exception("Not all required parameters are declared");

			fms::SortMode sortMode{ (param.find("-d") != param.end()) ? (fms::SortMode::decrease) : fms::SortMode::increase };

			if ((param.find("-s") == param.find("-i")))
				throw std::exception("Required data type parameter is not declared (-s / -i).");

			fms::SortType sortType{ (param.find("-s") != param.end()) ? fms::SortType::string : fms::SortType::integer };

			std::vector<std::string> inputFileNames;


			for (int i = 1; i < argc; i++)
			{
				if (fms::isFileHasRightFormat(argv[i], ".txt"))
					inputFileNames.push_back(argv[i]);
			}

			if (inputFileNames.size() < 2)
				throw std::exception("Input/output file paths are not specified");

			std::string outputFileName{ inputFileNames[0] };
			inputFileNames.erase(inputFileNames.begin());


			fms::FileMergeSort fileMergeSort(inputFileNames, outputFileName, sortMode, sortType, 1*1000*1000);
			fileMergeSort.debug_getFileIO()->printFilesData();
		}
		catch (const std::exception& e)
		{
			std::cerr << "A critical error was detected while running the program: \""<< e.what() <<"\"." << std::endl;
		}

	std::cin.get();

}