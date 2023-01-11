#include "./unexpected_handler.hpp"
#include "../io.hpp"

namespace posix {

	[[noreturn]] void unexpected_handler() {
		posix::abort();
	}

	[[noreturn]] void unexpected_handler(posix::error e) {
		std_err.write_from(e.to_string().sized());
		posix::abort();
	}

}