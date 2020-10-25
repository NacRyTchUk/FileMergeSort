#ifndef FILE_MERGE_SORT_IO
#define FILE_MERGE_SORT_IO

namespace fms {
	const int MAX_LINE_BUFFER_SIZE = 1024;

	class FileIO {
	public:
		
		FileData* getFilesData() { return _filesData; }
		

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
			if (_filesData[fileInd].getFile()->eof())
				_filesData[fileInd].changeType(FileType::closed);
			_filesData[fileInd].getFile()->getline(buffer, bufferSize);
		}

		

		FileIO(std::vector<std::string> inputFileNames, std::string outputFileName) {

			_filesDataCount = inputFileNames.size() + 1;

			_filesData = new FileData[_filesDataCount]{};

			_filesData[0].setData(outputFileName, FileType::output);

			_readBuffer = new char[MAX_LINE_BUFFER_SIZE];


			for (int i = 1; i < _filesDataCount; ++i)
				_filesData[i].setData(inputFileNames[i - 1], FileType::input);
			
			initializeValidFileList();
		}

		~FileIO() {

			for (int i = 0; i < _validFilesCout; i++)
				if ((_filesData[i].getType() != FileType::closed) && (_filesData[i].getType() != FileType::corrupt))
					_validFiles[i]->close();

			delete[] _readBuffer;

			delete[] _filesData;
		}

	private:
		FileData* _filesData;
		std::fstream** _validFiles;
		std::vector<FileData> _tempFilesData;
		int _filesDataCount, _validFilesCout;
		char* _readBuffer;


		void clearBuffer(char * buffer, int size = MAX_LINE_BUFFER_SIZE, char value = '\0') {
			for (int i{}; i < size; ++i)
				buffer[i] = value;
		}

		void initializeValidFileList() {
			_validFiles = new std::fstream * [_filesDataCount];
		
			if (_filesData[0].getType() == FileType::corrupt)
				throw  std::exception("Unable to create output file");

			for (int i = 0; i < _filesDataCount; i++)
				if (_filesData[i].getType() != FileType::corrupt) {
					_validFilesCout++;
					_validFiles[i] = _filesData[i].getFile();
					if (i > 0) _validFiles[i]->open(_filesData[i].getName(), std::ios_base::in);
				}

			if (_validFilesCout < 2)
				throw  std::exception("No input files were found, or all input files were corrupted");

			_validFiles[0]->open(_filesData[0].getName(), std::ios_base::out | std::ios_base::trunc);
			
		}
	};
}

#endif
