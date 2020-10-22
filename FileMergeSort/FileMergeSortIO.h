#ifndef FILE_MERGE_SORT_IO
#define FILE_MERGE_SORT_IO

namespace fms {

	class FileIO {
	public:
		FileIO(std::vector<std::string> inputFileNames, std::string outputFileName) {

			_filesCount = inputFileNames.size() + 1;

			_filesData = new FileData[_filesCount]{};

			_filesData[0].setData(outputFileName, FileType::output);

			for (int i = 1; i < _filesCount; ++i)
				_filesData[i].setData(inputFileNames[i - 1], FileType::input);
		}

		void printFilesData() {
			for (int i = 0; i < _filesCount; i++)
			{
				std::cout << "Files name: " << _filesData[i].getName() << "; File type: " << (int)_filesData[i].getType() << std::endl;
			}
		}

	private:
		FileData* _filesData;
		int _filesCount;
	};
}

#endif
