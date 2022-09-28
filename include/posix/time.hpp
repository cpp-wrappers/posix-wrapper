#pragma once

#include <integer.hpp>

extern "C" int clock_gettime(int32 clock_id, void* tp);

namespace posix {

#ifdef __MINGW32__
	struct seconds_and_nanoseconds {
		uint64 seconds;
		uint32 nanoseconds;
	};
#else
static_assert(false);
#endif

	struct clock {
		int32 id_;

		seconds_and_nanoseconds secods_and_nanoseconds() const {
			seconds_and_nanoseconds t;
			clock_gettime(id_, &t);
			return t;
		}

	};

#ifdef __MINGW32__
	static constexpr clock monolitic_clock{ 1 };
#else
static_assert(false);
#endif

}