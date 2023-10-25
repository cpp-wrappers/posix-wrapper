#pragma once

#include "./error.hpp"

namespace posix {

	struct unhandled_t {
		[[noreturn]] void operator () () const;
		[[noreturn]] void operator () (posix::error) const;
	};

	static constexpr unhandled_t unhandled{};

}