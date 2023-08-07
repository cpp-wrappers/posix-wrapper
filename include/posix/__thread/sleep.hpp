#pragma once

#include "../time.hpp"
#include "../error.hpp"

extern "C" int nanosleep (
	const struct timespec* requested_time,
	struct timespec* remaining
);

namespace posix {

	template<typename OnError>
	void nanosleep(
		seconds_and_nanoseconds time_requested,
		OnError&& on_error
	) {
		int result = ::nanosleep(
			(const struct timespec*) &time_requested,
			nullptr
		);
		if(result == 0) {
			return;
		}
		on_error(posix::latest_error());
	}

}