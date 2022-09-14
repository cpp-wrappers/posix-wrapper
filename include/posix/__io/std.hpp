#pragma once

#ifdef __MINGW32__

#include "./file.hpp"

extern "C" void* __acrt_iob_func(unsigned index);

namespace posix {

	inline file std_in()  { return file{ 0 }; }
	inline file std_out() { return file{ 1 }; }
	inline file std_err() { return file{ 2 }; }

}

#else
static_assert(false);
#endif