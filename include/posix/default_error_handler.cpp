#include "./error_handler.hpp"
#include "./io.hpp"

namespace posix {

	[[ noreturn ]]
	void error_handler(posix::error e) {
		std_err().write_from(e.to_string().sized());
		abort();
	}

}