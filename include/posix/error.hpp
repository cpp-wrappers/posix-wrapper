#pragma once

#include <c_string.hpp>

extern "C" char* strerror(int errnum);

namespace posix {

struct error {
	int value_;

	operator int() const {
		return value_;
	}

	c_string_of_unknown_size to_string() const {
		return { strerror(value_) };
	}

};

}

#ifdef __MINGW32__
	extern "C" int* _errno(void);

	namespace posix {
		inline error latest_error() {
			return { *_errno() };
		}
	}
#else
static_assert(false);
#endif