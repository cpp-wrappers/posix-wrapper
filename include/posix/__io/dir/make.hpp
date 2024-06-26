#pragma once

#include <c_string.hpp>
#include "../status.hpp"
#include "../../error.hpp"
#include "../../unhandled.hpp"

// #include <sys/stat.h>

extern "C" int mkdir(const char *path, posix::file_modes mode);

namespace posix {

	template<typename ErrorHandler>
	void try_make_dir(
		c_string<char> path,
		posix::file_modes modes,
		ErrorHandler&& error_handler
	) {
		int result = ::mkdir(path.iterator(), modes);
		if(result != 0) {
			error_handler(posix::latest_error());
		}
	}

	/*template<basic_range Path, typename ErrorHandler>
	void try_make_dir(
		Path&& path,
		posix::file_modes modes,
		ErrorHandler&& error_handler
	) {
		view_on_stack_as_c_string(
			forward<Path>(path),
			[&](c_string<char> path) {
				try_make_dir(path, modes, forward<ErrorHandler>(error_handler));
			}
		);
	}*/

	inline void make_dir(
		c_string<char> path,
		posix::file_modes access_modes
	) {
		return try_make_dir(
			path, access_modes, posix::unhandled
		);
	}

}