#include <iostream>

#ifndef BUFFER_H
#define BUFFER_H


namespace fms {

	class Buffer {
	public:
		Buffer(uint32_t bufferByteSize) {
			_bufferSize = bufferByteSize;
			_buffer = new char[bufferByteSize + 1] {};
		}

		~Buffer() {
			delete[] _buffer;
		}
	private:
		char* _buffer;
		uint32_t _bufferSize;
		uint32_t _bufferIterator{};
	};
}

#endif