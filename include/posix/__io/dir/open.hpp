#pragma once

#include "./types.hpp"
#include "../../error.hpp"
#include "../../unhandled.hpp"

#include <integer.hpp>
#include <c_string.hpp>
#include <expected.hpp>

extern "C" struct DIR* opendir(const char *dirname);

namespace posix {

	inline expected<handle<posix::dir>, posix::error>
	try_open_dir(c_string<char> dir_name) {
		auto result = (posix::dir*) ::opendir(dir_name.iterator());
		if(result == nullptr) {
			return unexpected{ posix::latest_error() };
		}
		return { result };
	}

	inline handle<posix::dir>
	open_dir(c_string<char> dir_name) {
		auto result = try_open_dir(dir_name);
		if(result.is_unexpected()) {
			posix::unhandled(result.get_unexpected());
		}
		return result.get_expected();
	}

}