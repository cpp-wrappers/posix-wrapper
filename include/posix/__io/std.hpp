#pragma once

#if __MINGW32__ || __gnu_linux__

#include "./file_descriptor.hpp"

extern "C" void* __acrt_iob_func(unsigned index);

namespace posix {

	static constexpr handle<file> std_in  { 0 };
	static constexpr handle<file> std_out { 1 };
	static constexpr handle<file> std_err { 2 };

}

#else
static_assert(false);
#endif