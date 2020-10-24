#ifndef FILE_MERGE_SORT_IO
#define FILE_MERGE_SORT_IO

namespace fms {

	class FileIO {
	public:
		

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
				throw new std::exception("Unable to create temp file");
			
			std::fstream * tempFileStream = _tempFilesData[_tempFilesData.size() - 1].getFile();

			int startInd{}, bufferValueSize{};
			while ((startInd < size) && (buffer[startInd] == '\0')) { startInd++; };
			while (((startInd + bufferValueSize) < size) && (buffer[startInd + bufferValueSize] != '\0')) { bufferValueSize++; };

			tempFileStream->open(_tempFilesData[_tempFilesData.size() - 1].getName(), std::ios_base::out | std::ios_base::trunc);
			tempFileStream->write((buffer + startInd), bufferValueSize);
			tempFileStream->close();
		}

		void writeInOutFile(char* buffer, int size) {
			_validFiles[0]->write(buffer, size);
		}

		FileIO(std::vector<std::string> inputFileNames, std::string outputFileName) {

			_filesDataCount = inputFileNames.size() + 1;

			_filesData = new FileData[_filesDataCount]{};

			_filesData[0].setData(outputFileName, FileType::output);

			for (int i = 1; i < _filesDataCount; ++i)
				_filesData[i].setData(inputFileNames[i - 1], FileType::input);

			initializeValidFileList();
		}

		~FileIO() {
			_validFiles[0]->close();
			delete[] _filesData;
		}

	private:
		FileData* _filesData;
		std::fstream** _validFiles;
		std::vector<FileData> _tempFilesData;
		int _filesDataCount, _validFilesCout;

		void initializeValidFileList() {
			_validFiles = new std::fstream * [_filesDataCount];

			if (_filesData[0].getType() == FileType::corrupt)
				throw new std::exception("Unable to create output file");
			
			for (int i = 0; i < _filesDataCount; i++)
				if (_filesData[i].getType() != FileType::corrupt)
					_validFiles[_validFilesCout++] = _filesData[i].getFile();

			_validFiles[0]->open(_filesData[0].getName(), std::ios_base::out | std::ios_base::trunc);


			if (_validFilesCout < 2)
				throw new std::exception("No input files were found, or all input files were corrupted");
		}
	};
}

#endif
