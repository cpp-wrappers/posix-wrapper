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

	enum class __seek {
		#if __MINGW32__ || __gnu_linux__
		set = 0,
		cur = 1,
		end = 2
		#else
		static_assert(false);
		#endif
	};
}

extern "C" posix::offset
lseek(int fd, posix::offset o, int whence);