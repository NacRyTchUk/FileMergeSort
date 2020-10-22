#include <iostream>
#include <fstream>
#include <string>

#ifndef MERGE_SORT_FILE_DATA
#define MERGE_SORT_FILE_DATA



namespace fms {

	enum class FileType
	{
		input, output, temp, corrupt
	};
	

	class FileData
	{
	public:
		std::string getName() { return _fileName; }
		FileType getType() { return _fileType; }

		void setData(std::string fileName, FileType fileType)
		{
			_fileName = fileName;
			_fileType = fileType;
		}


		FileData() {}

		FileData(std::string fileName, FileType fileType)
		{
			_fileName = fileName;
			_fileType = fileType;
		}

	private:
		std::string _fileName{};
		FileType _fileType{FileType::corrupt};
	};
}
#endif
