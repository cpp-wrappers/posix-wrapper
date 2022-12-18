#pragma once

namespace posix {

	enum mutex_attribute_type {
	#if __MINGW64__
		normal = 0,
		error_checking = 1,
		recursive = 2
	#else
		static_assert(false)
	#endif
	};

}