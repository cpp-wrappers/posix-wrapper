#pragma once

#include <c_string.hpp>
#include "../status.hpp"
#include "../../error.hpp"
#include "../../unhandled.hpp"

// #include <sys/stat.h>

extern "C" int mkdir(const char *path, posix::file_modes mode);

namespace posix {

	template<any_c_string<char> Path, typename ErrorHandler>
	void try_make_dir(
		Path&& path,
		posix::file_modes modes,
		ErrorHandler&& error_handler
	) {
		int result = ::mkdir(path.iterator(), modes);
		if(result != 0) {
			error_handler(posix::latest_error());
		}
	}

	template<basic_range Path, typename ErrorHandler>
	void try_make_dir(
		Path&& path,
		posix::file_modes modes,
		ErrorHandler&& error_handler
	) {
		view_on_stack_as_c_string(
			forward<Path>(path),
			[&](c_string_of_known_size<char> path) {
				try_make_dir(path, modes, forward<ErrorHandler>(error_handler));
			}
		);
	}

	template<basic_range Path>
	void make_dir(
		Path&& path,
		posix::file_modes access_modes
	) {
		return try_make_dir(
			forward<Path>(path), access_modes, posix::unhandled
		);
	}

}