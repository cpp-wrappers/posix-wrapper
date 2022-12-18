#pragma once

#include "./library.hpp"

#include <optional.hpp>
#include <c_string.hpp>

namespace posix {

	enum class open_library_flag {
		lazy,
		now
	};

	inline optional<body<posix::library>>
	try_open_library(c_string_of_unknown_size file, open_library_flag flag) {
		
	}

}