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

		void isExist() {
			if (_file.is_open() == true)
				return;
			
			if (_fileType == FileType::input)
			{
				std::fstream fs(_fileName);
				if (fs.is_open() == false)
					_fileType = FileType::corrupt;
				fs.close();
			}
			else
			{
				std::ofstream of(_fileName);
				if (of.is_open() == false)
					_fileType = FileType::corrupt;
				of.close();
			}
		}
	};
}
#endif
