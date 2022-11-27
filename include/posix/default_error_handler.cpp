#include "./error_handler.hpp"
#include "./io.hpp"

namespace posix {

	void error_handler(posix::error e) {
		no_return_error_handler(e);
	}

	[[noreturn]] void no_return_error_handler(posix::error e) {
		std_err.write_from(e.to_string().sized());
		posix::abort();
	}

}