
#ifndef SORT_PARAMETRS_H
#define SORT_PARAMETRS_H

namespace fms {
	enum class SortType
	{
		integer, string
	};

	enum class SortMode {
		decrease = -1, increase = 1
	};

	enum class FileType
	{
		input, output, temp, corrupt, closed
	};
}

#endif