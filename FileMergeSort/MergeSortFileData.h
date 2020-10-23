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

			open();
		}



		FileData() {}

		FileData(std::string fileName, FileType fileType)
		{
			setData(fileName, fileType);
		}

		~FileData() {
			if (_file.is_open())
			{
				_file.close();
				std::cout << _fileName << " has been closed" << std::endl;
			}
		}

	private:
		std::string _fileName{};
		FileType _fileType{FileType::corrupt};
		std::fstream _file;

		void open() {
			if (_fileType == FileType::corrupt)
				return;

			_file.open(_fileName, (_fileType == FileType::input) * (std::ios_base::in) +
					((_fileType == FileType::output) || (_fileType == FileType::temp)) * (std::ios_base::out | std::ios_base::trunc));

			if (_file.is_open() == false)
			{
				std::cerr << _fileName << " not found" << std::endl;
				_fileType = FileType::corrupt;
			}
		}
	};
}
#endif
