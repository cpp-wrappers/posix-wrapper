#pragma once

extern "C" __attribute__ ((__noreturn__)) void abort();

namespace posix {

	[[noreturn]] inline void abort() noexcept {
		::abort();
	}

}