#include "MergeSortFileData.h"
#include "FileMergeSortIO.h"
#include "Buffer.h"

#ifndef FILE_MERGE_SORT
#define FILE_MERGE_SORT

namespace fms {
	bool isBigger(char* a, char* b);

	class FileMergeSort {
	public:
		FileIO* debug_getFileIO() { return _fileIO; }


		FileMergeSort(std::vector<std::string> inputFileNames, std::string outputFileName, SortMode sortMode, uint32_t bufferByteSize) {
			_sortMode = sortMode;

			
			_fileIO = new FileIO(inputFileNames, outputFileName);

			_smartBuffer = new SmartBuffer(bufferByteSize, _sortMode, _fileIO);


			char ch[5]{'0','0','\n'};


			for (int i = 0; i < 10; i++)
			{
				ch[0] = i + '0';
				for (int j = 0; j < 4; j++)
				{
					//ch[1] = j + '0';
					//_smartBuffer->push(ch, 3);
					_fileIO->writeInOutFile(ch, 5);

				}
			}
		}

		~FileMergeSort() {
			delete _smartBuffer;
			delete _fileIO;
			std::cout << "buffer cleaned" << std::endl;
		}
	private:
		SmartBuffer * _smartBuffer;
		FileIO* _fileIO;
		SortMode _sortMode;
	};
}

#endif
