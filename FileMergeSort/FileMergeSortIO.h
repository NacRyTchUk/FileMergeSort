#include <sstream>

#ifndef FILE_MERGE_SORT_IO
#define FILE_MERGE_SORT_IO

namespace fms {
	const int MAX_LINE_BUFFER_SIZE = 1024;


	

	class FileIO {
		
	public:

		void writeInNewFile(const char * buffer, int size) {
			FileData fd("~" + std::to_string(_tempFilesData.size()) + ".temp", FileType::temp);
			
			if (fd.getType() == FileType::corrupt)
				throw std::exception("Unable to create temp file");
			
			_tempFilesData.push_back(fd);
			
			std::fstream * tempFileStream = _tempFilesData[_tempFilesData.size() - 1].getFile();

			int startInd{}, bufferValueSize{};
			while ((startInd < size) && (buffer[startInd] == '\0')) { startInd++; };
			while (((startInd + bufferValueSize) < size) && (buffer[startInd + bufferValueSize] != '\0'))
			{ bufferValueSize++; };

			tempFileStream->open(_tempFilesData[_tempFilesData.size() - 1].getName(), std::ios_base::out | std::ios_base::trunc);
			tempFileStream->write((buffer + startInd), bufferValueSize);
			tempFileStream->close();
		}

		void writeInOutFile(const char* buffer, int size = MAX_LINE_BUFFER_SIZE) {
			int startInd{}, bufferValueSize{};
			while ((startInd < size) && (buffer[startInd] == '\0')) { startInd++; };
			while (((startInd + bufferValueSize) < size) && (buffer[startInd + bufferValueSize] != '\0')) { bufferValueSize++; };
			_output_file->write((buffer + startInd), bufferValueSize);
		}

		void finalize(SortMode sortMode) {
			if (sortMode != SortMode::decrease)
				return;

			std::fstream* curTempFile;
			char* readBuffer = new char[MAX_LINE_BUFFER_SIZE];
			for (int i = _tempFilesData.size() - 1; i >= 0 ; --i)
			{
				curTempFile = _tempFilesData[i].getFile();

				curTempFile->open(_tempFilesData[i].getName(), std::ios_base::in);

				while ((curTempFile->eof() == false) )
				{
					_clearBuffer(readBuffer);
					curTempFile->getline(readBuffer, MAX_LINE_BUFFER_SIZE);
					if ((strlen(readBuffer) > 0)) readBuffer[strlen(readBuffer)] = '\n';
					writeInOutFile(readBuffer);
				}

				curTempFile->close();
				std::string fileName{ _tempFilesData[i].getName() };
				char* chFileName = new char[fileName.length() + 1];
				for (int i = 0; i < fileName.length(); i++)
					chFileName[i] = fileName[i];
				chFileName[fileName.length()] = '\0';
				std::remove(chFileName);
				delete []chFileName;
			}
			delete[] readBuffer;
		}

		void readLineFrom(int fileInd, char * buffer, int bufferSize) {
			_input_files[fileInd]->getline(buffer, bufferSize);
		}

		FileIO(std::vector<std::string> inputFileNames, std::string outputFileName) {

			_readBuffer = new char[MAX_LINE_BUFFER_SIZE];
			
			_input_files = new std::fstream * [inputFileNames.size()];

			_output_file = new std::fstream(outputFileName, std::ios_base::out | std::ios_base::trunc);
			if (_output_file->is_open() == false)
				throw  std::exception("Unable to create output file");

			_input_files_count = 0;

			for (int i = 1; i <= inputFileNames.size(); ++i) {
				std::fstream* file_to_check = new std::fstream(inputFileNames[i - 1], std::ios_base::in);
				if (file_to_check->is_open() == true)
					_input_files[_input_files_count++] = file_to_check;
				else
					delete file_to_check;
			}

			if (_input_files_count < 1)
				throw  std::exception("No input files were found, or all input files were corrupted");
		}

		~FileIO() {
			for (int i = 0; i < _input_files_count; i++)
				if (_input_files[i]->is_open())	_input_files[i]->close();
			if (_output_file->is_open()) _output_file->close();
			
			for (int i = 0; i < _input_files_count; i++)
				delete _input_files[i];
			delete[] _input_files;
			delete _output_file;
			delete[] _readBuffer;
		}


		class Multi_files_iterator {
		public:
			int get_files_count() { return __input_files.size(); }

			const std::vector<char*>& operator*() { return __current_bottom_values; }
			const char* operator[](int index) { return __current_bottom_values[index]; }
			bool operator==(const  Multi_files_iterator& f_iterator) { return __input_files == f_iterator.__input_files; }
			bool operator!=(const  Multi_files_iterator& f_iterator) { return __input_files != f_iterator.__input_files; }
			
			Multi_files_iterator(nullptr_t) {}

			Multi_files_iterator(FileIO *fileIO) {
				__fileIO = fileIO;

				__files_count = __fileIO->_input_files_count;

				for (int i{}; i < __files_count; ++i)
					__current_bottom_values.push_back(new char[MAX_LINE_BUFFER_SIZE] {0});

				for (int i = 0; i < __files_count; i++)
					__input_files.push_back(__fileIO->_input_files[i]);

				int* reread_indexes = new int[__files_count];
				for (int i = 0; i < __files_count; i++)
					reread_indexes[i] = i;
				next(reread_indexes, __files_count);
				delete[] reread_indexes;
			}

			~Multi_files_iterator() {
				for (int i = 0; i < __current_bottom_values.size(); i++)
					delete[] __current_bottom_values[i];
			}

			void remove(int index_of_elem) {
				delete[] __current_bottom_values[index_of_elem];
				__input_files.erase(__input_files.begin() + index_of_elem);
				__current_bottom_values.erase(__current_bottom_values.begin() + index_of_elem);
			}
			
			const std::vector<char*>& next(int* reread_indexes, int count_of_reread_indexes) {

				for (int i = count_of_reread_indexes - 1; i >=0; --i) {
				//	if (__input_files[reread_indexes[i]]->eof() == true) {
					//	__fileIO->_clearBuffer(__current_bottom_values[reread_indexes[i]], MAX_LINE_BUFFER_SIZE, EOF); continue; }
					__fileIO->_clearBuffer(__current_bottom_values[reread_indexes[i]]);
					__input_files[reread_indexes[i]]->getline(__current_bottom_values[reread_indexes[i]], MAX_LINE_BUFFER_SIZE);
				}
				return __current_bottom_values;
			}
			
		private:
			FileIO* __fileIO;
			std::vector<std::fstream*> __input_files;
			std::vector<char*> __current_bottom_values;
			int  __files_count;
		};

		const Multi_files_iterator end() { return _end_iterator; }

	private:
		std::fstream* _output_file;
		std::fstream** _input_files;
		std::vector<FileData> _tempFilesData;
		char* _readBuffer;
		int _input_files_count;
		Multi_files_iterator _end_iterator{nullptr};

		void _clearBuffer(char * buffer, int size = MAX_LINE_BUFFER_SIZE, char value = '\0') {
			for (int i{}; i < size; ++i)
				buffer[i] = value;
		}
	};
}
#endif
