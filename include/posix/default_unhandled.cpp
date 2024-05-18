#include "./unhandled.hpp"
#include "./io.hpp"
#include "./abort.hpp"

namespace posix {

	[[noreturn]] void unhandled_t::operator () () const {
		posix::abort();
	}

	[[noreturn]] void unhandled_t::operator () (posix::error e) const {
		auto str = e.to_string();
		std_err.write_from(str, range{str}.get_or_compute_size());
		posix::abort();
	}

}