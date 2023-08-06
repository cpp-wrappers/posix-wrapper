#pragma once

namespace posix {

	enum mutex_attribute_type {
	#if __MINGW32__
		normal = 0,
		error_checking = 1,
		recursive = 2
	#elif __linux__
		normal = 0,
		recursive = 1,
		error_checking = 2
	#else
		static_assert(false)
	#endif
	};

}