#pragma once

#include "./file.hpp"
#include "../error_handler.hpp"

#include <enum_flags.hpp>
#include <body.hpp>
#include <expected.hpp>

extern "C" int open(const char *path, int oflag, ...);

namespace posix {

	inline
	expected<body<posix::file>, posix::error>
	try_open_file(
		c_string_of_unknown_size name,
		file_access_modes modes
	) {
		int fd = ::open(name.iterator(), (int) modes);
		if(fd == -1) {
			return { posix::latest_error() };
		}
		return body<posix::file>{ fd };
	}

	inline body<posix::file> open_file(
		any_c_string auto name, file_access_modes modes
	) {
		expected<body<posix::file>, posix::error> result = try_open_file(
			name, modes
		);
		if(result.is_unexpected()) {
			posix::error_handler(result.get_unexpected());
		}
		return move(result).get_expected();
	}

}