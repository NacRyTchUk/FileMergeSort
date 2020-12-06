#include <iostream>
#include <ctime>
#include <vector>
#include <set>
#include "FileMergeSort.h"
#include "boost\program_options.hpp"

/*/
===========TODO=============
~Multithreading for pushing in buffer
~Read-all file instead of read-each-line in finalization part
++++++++++++multi-file iterator realization
~std::boost start option
~snake case lmao
~test for exception handled
~test for big (really big) files

*/

int main(int argc, char* argv[]) {
	/*namespace po = boost::program_options;
	po::options_description desc("General option");
	std::string input_type;

	desc.add_options()
		("inc,a","123")
		("dec,d", "321");

	po::variables_map vm;
	po::parsed_options parsed = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
	po::store(parsed, vm);
	po::notify(vm);*/


		try
		{
			std::set<std::string> cmdParam;
			for (int i = 1; i < argc; i++)
				cmdParam.insert(argv[i]);

			if (cmdParam.size() < 3)
				throw std::exception("Not all required parameters are declared");

			fms::SortMode sortMode{ (cmdParam.find("-d") != cmdParam.end()) ? (fms::SortMode::decrease) : fms::SortMode::increase };

			if ((cmdParam.find("-s") == cmdParam.find("-i")))
				throw std::exception("Required data type parameter is not declared (-s / -i).");

			fms::SortType sortType{ (cmdParam.find("-i") != cmdParam.end()) ? fms::SortType::integer : fms::SortType::string };

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
			
			std::cout << std::endl << "Sorting is complete, check the output file" << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cerr << "A critical error was detected while running the program: \""<< e.what() <<"\"." << std::endl;
		}
}