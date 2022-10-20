#ifndef POSIX_ERROR_HANDLER_HEADER

#include "error.hpp"
#include "abort.hpp"

namespace posix {

	void error_handler(posix::error);

}

#else
#include_next POSIX_ERROR_HANDLER_HEADER
#endif