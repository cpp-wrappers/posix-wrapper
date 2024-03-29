#include "./unhandled.hpp"
#include "./io.hpp"

namespace posix {

	[[noreturn]] void unhandled_t::operator () () const {
		posix::abort();
	}

	[[noreturn]] void unhandled_t::operator () (posix::error e) const {
		std_err.write_from(e.to_string().sized());
		posix::abort();
	}

}