#pragma once

#include <integer.hpp>

namespace posix {

	#if _WIN64 || __gnu_linux__
		using ticks_t = long;
	#endif

	#if _WIN64
		constexpr ticks_t ticks_per_second = 1000;
	#elif __gnu_linux__
		constexpr ticks_t ticks_per_second = 1000000;
	#else
		static_assert(false);
	#endif

	struct seconds_and_nanoseconds {
	#if _WIN64
		uint64 seconds;
		uint32 nanoseconds;
	#elif __gnu_linux__
		long seconds;
		long nanoseconds;
	#else
		static_assert(false);
	#endif
	};

}


extern "C" posix::ticks_t clock();
extern "C" int clock_gettime(int clock_id, struct timespec* tp);

namespace posix {

	struct clock {
		int id_;

		seconds_and_nanoseconds secods_and_nanoseconds() const {
			seconds_and_nanoseconds t;
			::clock_gettime(id_, (struct timespec*) &t);
			return t;
		}

	};

	inline ticks_t get_ticks() {
		return ::clock();
	}

#if _WIN64 || __gnu_linux__
	static constexpr clock monolitic_clock{ 1 };
#else
static_assert(false);
#endif

}