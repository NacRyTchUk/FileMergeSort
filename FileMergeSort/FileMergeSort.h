#include "MergeSortFileData.h"
#include "FileMergeSortIO.h"
#include "Buffer.h"
#include "SortParameters.h"


#ifndef FILE_MERGE_SORT
#define FILE_MERGE_SORT

namespace fms {


	bool isBigger(char*, char*, SortType);
	bool isFileHasRightFormat(const char*, std::string);
	
	

	class FileMergeSort {
	public:
		

		FileIO* debug_getFileIO() { return _fileIO; }


		void sort() {
			char symbolOfNewLine = '\n';
			while (_countOfRereadIndex > 0) {
				FileData* filesData = _fileIO->getFilesData();
				if (_countOfRereadIndex < 1)
					return;

				for (int i = 0; i < _countOfRereadIndex; i++)
					if (filesData[_indexForReread[i] + 1].getType() == FileType::input)
					{
						_clearBuffer(_valueBuffer);
						_fileIO->readLineFrom(_indexForReread[i] + 1, _valueBuffer, MAX_LINE_BUFFER_SIZE);
						if (isBigger(_currentBottomValues[_indexForReread[i]], _valueBuffer, _sortType))
							//throw std::exception("Incorrectly sorted file");
						{
							filesData[_indexForReread[i] + 1].changeType(FileType::corrupt);
							std::cerr << "A non-critical error was detected: the file \"" << filesData[_indexForReread[i] + 1].getName() <<
								"\" was sorted Incorrectly. Sorting will continue with data loss." << std::endl;
							continue;
						}
						_clearBuffer(_currentBottomValues[_indexForReread[i]]);
						strcat_s(_currentBottomValues[_indexForReread[i]], MAX_LINE_BUFFER_SIZE, _valueBuffer);
					}


				_countOfRereadIndex = 0;
				int minInd{ -1 };
				while ((filesData[++minInd + 1].getType() != FileType::input) && (minInd < _inputFilesCount)) {}

				for (int i = minInd; i < _inputFilesCount; i++)
				{
					if (filesData[i + 1].getType() == FileType::input)
					{
						if (isBigger(_currentBottomValues[minInd], _currentBottomValues[i], _sortType))
						{
							minInd = i;
							_countOfRereadIndex = 0;
						}
						if (strcmp(_currentBottomValues[minInd], _currentBottomValues[i]) == 0)
							_indexForReread[_countOfRereadIndex++] = i;
					}
				}

				
				for (int i = 0; i < _countOfRereadIndex; i++)
				{

					_smartBuffer->push(_currentBottomValues[minInd], strlen(_currentBottomValues[minInd]));
					_smartBuffer->push(&symbolOfNewLine, 1);
				}
			}

			_smartBuffer->forceBufferClear();

			_fileIO->finalize(_sortMode);
		}

		FileMergeSort(std::vector<std::string> inputFileNames, std::string outputFileName, SortMode sortMode, SortType sortType, uint32_t bufferByteSize) {
			_sortMode = sortMode;
			_sortType = sortType;
			
			_fileIO = new FileIO(inputFileNames, outputFileName);

			_smartBuffer = new SmartBuffer(bufferByteSize, _sortMode, _fileIO);
			_valueBuffer = new char[MAX_LINE_BUFFER_SIZE];

			_inputFilesCount = inputFileNames.size();
			 _currentBottomValues = new char*[_inputFilesCount];
			for (int i{}; i < _inputFilesCount; ++i)
				_currentBottomValues[i] = new char[MAX_LINE_BUFFER_SIZE] {0};
			_indexForReread = new int[_inputFilesCount];
			for (int i{ 0 }; i < _inputFilesCount; ++i)
				_indexForReread[i] = i;
			_countOfRereadIndex = _inputFilesCount;


		}

		~FileMergeSort() {
			delete _smartBuffer;
			
			
			delete _fileIO;


			for (int i = 0; i < _inputFilesCount; i++)
				delete [] _currentBottomValues[i];
			delete[] _currentBottomValues;
			delete[] _valueBuffer;
			delete[] _indexForReread;
			std::cout << "buffer cleaned" << std::endl;
		}
	private:
		SmartBuffer * _smartBuffer;
		FileIO* _fileIO;
		SortMode _sortMode;
		SortType _sortType;


		char** _currentBottomValues;
		char* _valueBuffer;
		int* _indexForReread;
		int  _countOfRereadIndex, _inputFilesCount;


		void _clearBuffer(char* buffer, int size = MAX_LINE_BUFFER_SIZE, char value = '\0') {
			for (int i{}; i < size; ++i)
				buffer[i] = value;
		}
	};
}

#endif
