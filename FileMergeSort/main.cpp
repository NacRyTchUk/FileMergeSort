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

			fms::SortType sortType{ (param.find("-i") != param.end()) ? fms::SortType::integer : fms::SortType::string };

			std::vector<std::string> inputFileNames;

			int64_t smartBufferSize{ 50 * 1000 * 1000 };
			int tempSize{};
			for (int i = 1; i < argc; i++)
			{
				if (fms::isFileHasRightFormat(argv[i], ".txt"))
					inputFileNames.push_back(argv[i]);

				if ((strcmp(argv[i - 1], "-b") == 0) && (tempSize = std::atoi(argv[i])))
					if (tempSize > 0 && tempSize <= 1000)
						smartBufferSize = (int64_t)tempSize * 1000 * 1000;
					else 
						std::cerr << "The buffer size is set incorrectly (" << tempSize << "mb)." << std::endl;

			}

			if (inputFileNames.size() < 2)
				throw std::exception("Input/output file paths are not specified");

			std::string outputFileName{ inputFileNames[0] };
			inputFileNames.erase(inputFileNames.begin());

			std::cout << "sortmode: " << (((int)sortMode == -1) ? "decrease" : "increase") << std::endl;
			std::cout << "sorttype: " << (((int)sortType == 0) ? "integer" : "string") << std::endl;
			std::cout << "output file: " << outputFileName << std::endl;
			std::cout << "buffer size (Bytes): " << smartBufferSize<< std::endl << std::endl;

			fms::FileMergeSort fileMergeSort(inputFileNames, outputFileName, sortMode, sortType, smartBufferSize);
			fileMergeSort.sort();

			fileMergeSort.debug_getFileIO()->printFilesData();
		}
		catch (const std::exception& e)
		{
			std::cerr << "A critical error was detected while running the program: \""<< e.what() <<"\"." << std::endl;
		}
}