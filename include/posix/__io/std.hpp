#pragma once

#ifdef __MINGW32__

#include "./file_descriptor.hpp"

extern "C" void* __acrt_iob_func(unsigned index);

namespace posix {

	inline file_descriptor std_in()  { return { 0 }; }
	inline file_descriptor std_out() { return { 1 }; }
	inline file_descriptor std_err() { return { 2 }; }

}

#else
static_assert(false);
#endif