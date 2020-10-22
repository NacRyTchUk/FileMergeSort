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


		FileMergeSort(std::vector<std::string> inputFileNames, std::string outputFileName, uint32_t bufferByteSize) {
			_streamBuffer = new Buffer(bufferByteSize);
			
			_fileIO = new FileIO(inputFileNames, outputFileName);
		}

		~FileMergeSort() {
			delete _streamBuffer;
			delete _fileIO;
			std::cout << "buffer cleaned" << std::endl;
		}
	private:
		Buffer * _streamBuffer;
		FileIO* _fileIO;
	};
}

#endif
