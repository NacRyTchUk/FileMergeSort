#include "MergeSortFileData.h"
#include "FileMergeSortIO.h"
#include "Buffer.h"
#include "SortParameters.h"


#ifndef FILE_MERGE_SORT
#define FILE_MERGE_SORT

namespace fms {


	

	bool isBigger(const char*, const char*, SortType);
	bool isFileHasRightFormat(const char*, std::string);

	class FileMergeSort {
	public:
		void sort() {
			const char symbolOfNewLine = '\n';
			
			FileIO::Multi_files_iterator mfit(_fileIO);
			std::vector<char*> last_values;
				for (size_t i = 0; i < mfit.get_files_count(); i++)	last_values.push_back(new char[MAX_LINE_BUFFER_SIZE] {});
			int min_indexes_count{};
			int* min_indexes = new int[mfit.get_files_count()];
				for (int i = 0; i < min_indexes_count; i++)	min_indexes[i] = i;

			while (mfit.get_files_count() > 0)
			{
				for (int i = min_indexes_count - 1; i >= 0 ; --i)
					if (isBigger(last_values[min_indexes[i]], mfit[min_indexes[i]], _sortType))
					{
						//=-=-=-=-=-=-=
						if (mfit[min_indexes[i]][0] != '\0') 
							std::cerr << "A non-critical error was detected: a file was sorted Incorrectly. Sorting will continue with data loss." << std::endl;
						mfit.remove(min_indexes[i]);
						last_values.erase(last_values.begin() + min_indexes[i]);
					}
					else strcpy_s(last_values[min_indexes[i]], MAX_LINE_BUFFER_SIZE, mfit[min_indexes[i]]);
				
				int minInd = min_indexes_count = 0;
				for (int i = minInd; i < mfit.get_files_count(); i++)
				{
					if (isBigger(mfit[minInd], mfit[i], _sortType)) minInd = i + (min_indexes_count = 0);
					if (strcmp(mfit[minInd], mfit[i]) == 0) min_indexes[min_indexes_count++] = i;
				}

				//place for multithreading
				for (int i = 0; i < min_indexes_count; i++)
				{
					_smartBuffer->push(mfit[minInd], strlen(mfit[minInd]));
					_smartBuffer->push(&symbolOfNewLine, 1);
				}
				mfit.next(min_indexes, min_indexes_count);
			}
			
			delete[] min_indexes;
			for (auto el : last_values)
				delete[] el;
			_smartBuffer->forceBufferClear();

			_fileIO->finalize(_sortMode);
		}

		FileMergeSort(std::vector<std::string> inputFileNames, std::string outputFileName, SortMode sortMode, SortType sortType, uint64_t bufferByteSize) {
			_sortMode = sortMode;
			_sortType = sortType;
			
			_fileIO = new FileIO(inputFileNames, outputFileName);

			_smartBuffer = new SmartBuffer(bufferByteSize, _sortMode, [&](const char* text, int textLength) {
					if (_sortMode == SortMode::decrease) _fileIO->writeInNewFile(text, textLength);
					else _fileIO->writeInOutFile(text,textLength);
				});
		}

		~FileMergeSort() {
		}
	private:
		SmartBuffer* _smartBuffer;
		FileIO* _fileIO;
		SortMode _sortMode;
		SortType _sortType;

		void _clearBuffer(char* buffer, int size = MAX_LINE_BUFFER_SIZE, char value = '\0') {
			for (int i{}; i < size; ++i)
				buffer[i] = value;
		}
	};
}

#endif
