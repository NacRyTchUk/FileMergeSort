#ifndef FILE_MERGE_SORT_IO
#define FILE_MERGE_SORT_IO

namespace fms {

	class FileIO {
	public:
		struct SortBatchElement
		{
			char* _prevValue, * _curValue;
			FileData* _fileData;
			bool _isNeedToReread{};
		public:
			char* getCurValue() { return _curValue; }
			char* getPrevValue() { return _prevValue; }
			bool isNeedToRereed() { return _isNeedToReread; }


			void init(char* initValue, FileData *fileData) {
				_prevValue = _curValue = initValue;
				_fileData = fileData;
			}

			void move(char* newValue) {
				_prevValue = _curValue;
				_curValue = _prevValue;
				_isNeedToReread = false;
				if (*_prevValue > * _curValue)
					throw std::exception("Incorrectly sorted file");
			}
		};

		void printFilesData() {
			for (int i = 0; i < _filesDataCount; i++)
			{
				std::cout << "Files name: " << _filesData[i].getName() << "; File type: " << (int)_filesData[i].getType() << std::endl;
			}
		}

		void writeInNewFile(char * buffer, int size) {
			FileData fd("~" + std::to_string(_tempFilesData.size()) + ".temp", FileType::temp);
			_tempFilesData.push_back(fd);

			if (_tempFilesData[_tempFilesData.size() - 1].getType() == FileType::corrupt)
				throw std::exception("Unable to create temp file");
			
			std::fstream * tempFileStream = _tempFilesData[_tempFilesData.size() - 1].getFile();

			int startInd{}, bufferValueSize{};
			while ((startInd < size) && (buffer[startInd] == '\0')) { startInd++; };
			while (((startInd + bufferValueSize) < size) && (buffer[startInd + bufferValueSize] != '\0')) { bufferValueSize++; };

			tempFileStream->open(_tempFilesData[_tempFilesData.size() - 1].getName(), std::ios_base::out | std::ios_base::trunc);
			tempFileStream->write((buffer + startInd), bufferValueSize);
			tempFileStream->close();
		}

		void writeInOutFile(char* buffer, int size) {
			int startInd{}, bufferValueSize{};
			while ((startInd < size) && (buffer[startInd] == '\0')) { startInd++; };
			while (((startInd + bufferValueSize) < size) && (buffer[startInd + bufferValueSize] != '\0')) { bufferValueSize++; };
			_validFiles[0]->write((buffer + startInd), bufferValueSize);
		}

		void readLineFrom(int fileInd, char * buffer, int bufferSize) {
			_validFiles[fileInd]->getline(buffer, bufferSize);
		}

		/*SortBunchElement* makeBanch() {
			if (_validFilesCout < 2)
				return;
		}*/

		FileIO(std::vector<std::string> inputFileNames, std::string outputFileName) {

			_filesDataCount = inputFileNames.size() + 1;

			_filesData = new FileData[_filesDataCount]{};
			batch = new SortBatchElement[_filesDataCount]{};

			_filesData[0].setData(outputFileName, FileType::output);

			for (int i = 1; i < _filesDataCount; ++i)
				_filesData[i].setData(inputFileNames[i - 1], FileType::input);
			
			initializeValidFileList();
		}

		~FileIO() {
			for (int i = 0; i < _validFilesCout; i++)
				_validFiles[i]->close();
			
			delete[] batch;

			delete[] _filesData;
		}

	private:
		FileData* _filesData;
		std::fstream** _validFiles;
		std::vector<FileData> _tempFilesData;
		SortBatchElement * batch;
		int _filesDataCount, _validFilesCout;


		

		void initializeValidFileList() {
			_validFiles = new std::fstream * [_filesDataCount];
		
			if (_filesData[0].getType() == FileType::corrupt)
				throw  std::exception("Unable to create output file");

			for (int i = 0; i < _filesDataCount; i++)
				if (_filesData[i].getType() != FileType::corrupt) {
					_validFiles[_validFilesCout++] = _filesData[i].getFile();
					if (i > 0) _validFiles[_validFilesCout - 1]->open(_filesData[i].getName(), std::ios_base::in);
				}

			if (_validFilesCout < 2)
				throw  std::exception("No input files were found, or all input files were corrupted");

			_validFiles[0]->open(_filesData[0].getName(), std::ios_base::out | std::ios_base::trunc);
			
		}
	};
}

#endif
