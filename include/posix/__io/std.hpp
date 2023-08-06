#pragma once

#if __MINGW32__ || __gnu_linux__

#include "./file.hpp"

extern "C" struct _iobuf* __acrt_iob_func(unsigned index);

namespace posix {

	static constexpr handle<posix::file> std_in  { 0 };
	static constexpr handle<posix::file> std_out { 1 };
	static constexpr handle<posix::file> std_err { 2 };

}

#else
static_assert(false);
#endif