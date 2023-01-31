#pragma once

#include "./file.hpp"
#include "../unhandled.hpp"

#include <enum_flags.hpp>
#include <body.hpp>
#include <expected.hpp>

extern "C" int open(const char *path, int oflag, ...);

namespace posix {

	inline expected<handle<posix::file>, posix::error> try_open_file(
		any_c_string auto name,
		file_access_modes modes
	) {
		int fd = ::open(name.iterator(), (int) modes);
		if(fd == -1) {
			return posix::latest_error();
		}
		return handle<posix::file>{ fd };
	}

	inline handle<posix::file> open_file(
		any_c_string auto name,
		file_access_modes modes
	) {
		expected<handle<posix::file>, posix::error> result
			= posix::try_open_file(
				name, modes
			);
		if(result.is_unexpected()) {
			posix::unhandled(result.get_unexpected());
		}
		return result.get_expected();
	}

}