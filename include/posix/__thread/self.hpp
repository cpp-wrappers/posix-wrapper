#pragma once

#include "./thread.hpp"

extern "C" posix::thread_handle_underlying pthread_self();

namespace posix {

	inline handle<posix::thread> self() {
		return { pthread_self() };
	}

}