#pragma once

#if __MINGW32__ || __gnu_linux__
	extern "C" int __isnan (double);
	extern "C" int __isnanf(float);
	extern "C" int __isnanl(long double);
#else
static_assert(false);
#endif

#include <type.hpp>

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

}