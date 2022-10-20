#pragma once

#include <integer.hpp>

extern "C" int clock_gettime(int clock_id, void* tp);

namespace posix {

	struct seconds_and_nanoseconds {
	#if __MINGW32__
		uint64 seconds;
		uint32 nanoseconds;
	#elif __gnu_linux__
		long seconds;
		long nanoseconds;
	#else
	static_assert(false);
	#endif
	};

	struct clock {
		int id_;

		seconds_and_nanoseconds secods_and_nanoseconds() const {
			seconds_and_nanoseconds t;
			clock_gettime(id_, &t);
			return t;
		}

	};

#if __MINGW32__ || __gnu_linux__
	static constexpr clock monolitic_clock{ 1 };
#else
static_assert(false);
#endif

}