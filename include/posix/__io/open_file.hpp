#pragma once

#include "./file.hpp"
#include "../unhandled.hpp"

#include <enum_flags.hpp>
#include <body.hpp>
#include <expected.hpp>
#include <optional.hpp>

// #include <fcntl.h>

extern "C" int open(const char *path, int oflag, ...);

namespace posix {

	inline expected<handle<posix::file>, posix::error> try_open_file(
		contiguous_range auto&& name,
		posix::file_access_modes access_modes
	) {
		int fd = ::open(
			(const char*) name.iterator(),
			(int) access_modes
		);
		if(fd == -1) {
			return posix::latest_error();
		}
		return handle<posix::file>{ fd };
	}

	inline expected<handle<posix::file>, posix::error> try_open_file(
		contiguous_range auto&& name,
		posix::file_access_modes access_modes,
		posix::file_modes file_modes
	) {
		int fd = ::open(
			(const char*) name.iterator(),
			(int) access_modes,
			file_modes
		);
		if(fd == -1) {
			return posix::latest_error();
		}
		return handle<posix::file>{ fd };
	}

	inline expected<handle<posix::file>, posix::error> try_open_file(
		c_string<char> name,
		posix::file_access_mode access_mode
	) {
		return try_open_file(
			name,
			posix::file_access_modes { access_mode }
		);
	}

	inline handle<posix::file> open_file(
		c_string<char> name,
		posix::file_access_modes access_modes
	) {
		expected<handle<posix::file>, posix::error> result
			= posix::try_open_file(
				name, access_modes
			);
		if(result.is_unexpected()) {
			posix::unhandled(result.get_unexpected());
		}
		return result.get_expected();
	}

	inline handle<posix::file> open_file(
		c_string<char> name,
		posix::file_access_modes access_modes,
		posix::file_modes file_modes
	) {
		expected<handle<posix::file>, posix::error> result
			= posix::try_open_file(
				name, access_modes, file_modes
			);
		if(result.is_unexpected()) {
			posix::unhandled(result.get_unexpected());
		}
		return result.get_expected();
	}

}