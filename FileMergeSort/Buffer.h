#include <iostream>

#ifndef BUFFER_H
#define BUFFER_H


namespace fms {


	class SmartBuffer {
	public:
		int getSize() { return _bufferSize; }

		void push(char* pushText, int textLength) {
			if (_sortMode == SortMode::increase)
				pushForward(pushText, textLength);
			else
				pushBack(pushText, textLength);
		}

		
		void forceBufferClear() {
			_fileIO->writeInNewFile(_buffer, _bufferSize);

			clearBuffer();
		}

		SmartBuffer(uint32_t bufferSize, SortMode sortMode, FileIO * fileIO) { //void (*pushFunc)(char*, int)
			_bufferSize = bufferSize;
			_buffer = new char[bufferSize + 1]{};
			_sortMode = sortMode;
			_fileIO = fileIO; //_pushFunc = pushFunc;
			clearBuffer();
		}


		~SmartBuffer() {
			delete[] _buffer;
		}

		operator char* () { return _buffer; }
	private:
		char* _buffer;
		int32_t _bufferSize; 
		int64_t _bufferIterator{};
		FileIO* _fileIO; //void (*_pushFunc)(char*, int);
		SortMode _sortMode;


		void clearBuffer() {
			for (int i = 0; i < _bufferSize; i++)
				_buffer[i] = '\0';
			_bufferIterator = (_sortMode == SortMode::decrease) * (_bufferSize - 1);
		}

		void pushBack(char* pushText, int textLength, int curLetter = CHAR_MIN) {

			curLetter = (curLetter == CHAR_MIN) ? textLength - 1 : curLetter;
			if (_bufferIterator - textLength + (curLetter != textLength - 1) * (curLetter) >= 0) {
				while (curLetter >= 0)
					_buffer[_bufferIterator--] = pushText[curLetter--];
			}
			else
			{

				while (_bufferIterator >= 0)
					_buffer[_bufferIterator--] = pushText[curLetter--];
				forceBufferClear();
				pushBack(pushText, textLength, curLetter);
			}
		}

		void pushForward(char* pushText, int textLength, int curLetter = 0) {
			/*if (_bufferIterator + textLength - curLetter < _bufferSize) {
				while (curLetter < textLength)
					_buffer[_bufferIterator++] = pushText[curLetter++];
			}
			else
			{
				while (_bufferIterator < _bufferSize)
					_buffer[_bufferIterator++] = pushText[curLetter++];
				_fileIO->writeInNewFile(_buffer, _bufferSize);
				clearBuffer();
				pushForward(pushText, textLength, curLetter);
			}*/
			_fileIO->writeInOutFile(pushText, textLength);
		}

		void fillWhileLower(int * aNumb, int*bNumb, char * fillText, int * incNumb = 0) {
			while (*aNumb < *bNumb)
				_buffer[_bufferIterator+=(int)_sortMode] = fillText[(*incNumb)++];
		}
	};
}

#endif