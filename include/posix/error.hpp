#pragma once

#include <c_string.hpp>

extern "C" char* strerror(int errnum);

namespace posix {

class error {
	int value_;
public:
	error(int value) : value_(value) {}
	error(const error& other) : value_(other.value_) {}

	int code() const {
		return value_;
	}

	c_string_of_unknown_size<char> to_string() const {
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
#elif __gnu_linux__
	extern "C" int* __errno_location();

	namespace posix {
		inline error latest_error() {
			return error{ *__errno_location() };
		}
	}

#else
static_assert(false);
#endif