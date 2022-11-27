#pragma once

#include "./file_descriptor.hpp"
#include "../error_handler.hpp"

#include <enum_flags.hpp>
#include <body.hpp>

extern "C" int open(const char *path, int oflag, ...);

namespace posix {

	template<typename ErrorHandler>
	inline optional<body<posix::file>> try_open_file(
		c_string_of_unknown_size name,
		file_access_modes modes,
		ErrorHandler error_handler
	) {
		int fd = ::open(name.iterator(), (int) modes);
		if(fd == -1) {
			error_handler(posix::latest_error());
			return {};
		}
		return body<posix::file>{ fd };
	}

	inline body<posix::file> open_file(
		any_c_string auto name, file_access_modes modes
	) {
		return move(try_open_file(name, modes, posix::error_handler).value());
	}

}