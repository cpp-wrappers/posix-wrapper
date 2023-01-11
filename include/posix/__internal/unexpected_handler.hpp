#ifndef POSIX_unexpected_handler_HEADER

#include "../error.hpp"
#include "../abort.hpp"

namespace posix {

	[[noreturn]] void unexpected_handler();
	[[noreturn]] void unexpected_handler(posix::error);

}

#else
#include_next POSIX_unexpected_handler_HEADER
#endif