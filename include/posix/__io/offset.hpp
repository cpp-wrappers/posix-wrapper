#pragma once

#include <integer.hpp>

namespace posix {

	using offset =
		#if __MINGW32__
		int32
		#elif __gnu_linux__
		long
		#else
		static_assert(false);
		#endif
	;

}