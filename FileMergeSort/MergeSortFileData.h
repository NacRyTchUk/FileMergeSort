#include <iostream>
#include <fstream>
#include <string>

#ifndef MERGE_SORT_FILE_DATA
#define MERGE_SORT_FILE_DATA



namespace fms {

	enum class FileType
	{
		input, output, temp, corrupt, closed
	};

	enum class SortMode {
		decrease = -1, increase = 1
	};
	

	class FileData
	{
	public:
		std::string getName() { return _fileName; }
		FileType getType() { return _fileType; }
		std::fstream * getFile() { return &_file; }


		void setData(std::string fileName, FileType fileType)
		{
			_fileName = fileName;
			_fileType = fileType;
			
		}

		FileData() {}

		FileData(const FileData& fd)
		{
			setData(fd._fileName, fd._fileType);
		}

		FileData(std::string fileName, FileType fileType)
		{
			setData(fileName, fileType); 
		}

	private:
		std::string _fileName{};
		FileType _fileType{FileType::corrupt};
		std::fstream _file;
	};
}
#endif
