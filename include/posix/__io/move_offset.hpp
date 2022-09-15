#pragma once

#include <integer.hpp>

namespace posix {
	using offset =
			#ifdef __MINGW32__
			int32;
			#else
			static_assert(false);
			#endif
	enum class __seek {
		#ifdef __MINGW32__
		cur = 1,
		end = 2,
		set = 0
		#else
		static_assert(false);
		#endif
	};
}

extern "C" posix::offset
lseek(int fd, posix::offset o, int whence);