#pragma once

extern "C" [[noreturn]] void abort() noexcept;

namespace posix {

	[[noreturn]] inline void abort() noexcept {
		::abort();
	}

}