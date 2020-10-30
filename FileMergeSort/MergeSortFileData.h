#include <iostream>
#include <fstream>
#include <string>
#include "SortParameters.h"


#ifndef MERGE_SORT_FILE_DATA
#define MERGE_SORT_FILE_DATA



namespace fms {

	class FileData
	{
	public:
		std::string getName() { return _fileName; }
		FileType getType() { return _fileType; }
		std::fstream * getFile() { return &_file; }

		void changeType(FileType newType) { _fileType = newType; }

		void setData(std::string fileName, FileType fileType)
		{
			_fileName = fileName;
			_fileType = fileType;
			isExist();
		}

		void setData(const FileData * fd) {
			setData(fd->_fileName,fd->_fileType);
		}

		FileData() {}

		FileData(const FileData& fd)
		{
			_fileName = fd._fileName;
			_fileType = fd._fileType;
		}

		FileData(std::string fileName, FileType fileType)
		{
			setData(fileName, fileType); 
		}

	private:
		std::string _fileName{};
		FileType _fileType{FileType::corrupt};
		std::fstream _file;

		void isExist() {
			if (_file.is_open() == true)
				return;
			
			std::fstream fs(_fileName, (_fileType != FileType::input) * std::ios::out + (_fileType == FileType::input));
			if (fs.is_open() == false)
				_fileType = FileType::corrupt;
			fs.close();
		}
	};
}
#endif
