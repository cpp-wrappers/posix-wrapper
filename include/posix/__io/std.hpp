#pragma once

#ifdef __MINGW32__

#include "./file_descriptor.hpp"

extern "C" void* __acrt_iob_func(unsigned index);

namespace posix {

	static constexpr file_descriptor std_in  { 0 };
	static constexpr file_descriptor std_out { 1 };
	static constexpr file_descriptor std_err { 2 };

}

#else
static_assert(false);
#endif