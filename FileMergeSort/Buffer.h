#include <iostream>

#ifndef BUFFER_H
#define BUFFER_H


namespace fms {


	class SmartBuffer {
	public:
		int getSize() { return _bufferSize; }

		void push(char* pushText, int textLength) {
			if (_sortMode == SortMode::increase)
				_pushForward(pushText, textLength);
			else
				_pushBack(pushText, textLength);
		}

		
		void forceBufferClear() {
			_fileIO->writeInNewFile(_buffer, _bufferSize);

			_clearBuffer();
		}

		SmartBuffer(uint64_t bufferSize, SortMode sortMode, FileIO * fileIO) { 
			_bufferSize = bufferSize;
			_buffer = new char[bufferSize + 1]{};
			_sortMode = sortMode;
			_fileIO = fileIO; 
			_clearBuffer();
		}


		~SmartBuffer() {
			delete[] _buffer;
		}

		operator char* () { return _buffer; }
	private:
		char* _buffer;
		int64_t _bufferSize, _bufferIterator{};
		FileIO* _fileIO; 
		SortMode _sortMode;


		void _clearBuffer() {
			for (int i = 0; i < _bufferSize; i++)
				_buffer[i] = '\0';
			_bufferIterator = (int)(_sortMode == SortMode::decrease) * (_bufferSize - 2);
		}

		void _pushBack(char* pushText, int textLength, int curLetter = CHAR_MIN) {
			curLetter = (curLetter == CHAR_MIN) ? textLength - 1 : curLetter;
			if (_bufferIterator - textLength + (int64_t)(curLetter != textLength - 1) * (curLetter) >= 0) {
				while (curLetter >= 0)
					_buffer[_bufferIterator--] = pushText[curLetter--];
			}
			else
			{
				while (_bufferIterator >= 0)
					_buffer[_bufferIterator--] = pushText[curLetter--];
				forceBufferClear();
				_pushBack(pushText, textLength, curLetter);
			}
		}

		void _pushForward(char* pushText, int textLength) {
			_fileIO->writeInOutFile(pushText, textLength);
		}

		void _fillWhileLower(int * aNumb, int*bNumb, char * fillText, int * incNumb = 0) {
			while (*aNumb < *bNumb)
				_buffer[_bufferIterator+=(int)_sortMode] = fillText[(*incNumb)++];
		}
	};
}

#endif