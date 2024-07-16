#pragma once

#if __MINGW32__ || __gnu_linux__
	extern "C" int __isnan (double);
	extern "C" int __isnanf(float);
	extern "C" int __isnanl(long double);
#else
static_assert(false);
#endif

#include <type.hpp>
#include "./error.hpp"
#include "./unhandled.hpp"

extern "C" float strtof(const char *str, char** end);
extern "C" double strtod(const char *str, char** end);
extern "C" unsigned long strtoul(const char* str, char** end, int base);

namespace posix {

	template<same_as<double> Type>
	bool is_nan(Type value) {
		return __isnan(value);
	}

	template<same_as<float> Type>
	bool is_nan(Type value) {
		return __isnanf(value);
	}

	template<same_as<long double> Type>
	bool is_nan(Type value) {
		return __isnanl(value);
	}

	inline float str_to_float(const char *str, char** end=nullptr) {
		float result = strtof(str, end);
		auto error = posix::latest_error();
		if (error.code() != 0) {
			posix::unhandled(error);
		}
		return result;
	}

	inline double str_to_double(const char *str, char** end=nullptr) {
		double result = strtod(str, end);
		auto error = posix::latest_error();
		if (error.code() != 0) {
			posix::unhandled(error);
		}
		return result;
	}

	inline unsigned long
	str_to_unsigned_long(const char *str, nuint base = 10, char** end=nullptr) {
		unsigned long result = strtoul(str, end, base);
		auto error = posix::latest_error();
		if (error.code() != 0) {
			posix::unhandled(error);
		}
		return result;
	}

}