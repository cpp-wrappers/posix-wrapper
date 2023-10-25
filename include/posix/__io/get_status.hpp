#pragma once

#include "./file.hpp"
#include "./status.hpp"
#include "../error.hpp"
#include "../unhandled.hpp"

#include <c_string.hpp>

extern "C" int fstat(int fildes, posix::status* buf);
extern "C" int stat(const char* path, posix::status* buf);
//extern "C" int fstatat(int fd, const char* path, posix::status* buf, int flag);

namespace posix {

	template<any_c_string<char> Path, typename ErrorHandler>
	inline optional<posix::status>
	try_get_file_status(
		Path&& path,
		ErrorHandler&& error_handler
	) {
		status s;
		int result = ::stat(path.iterator(), &s);
		if(result != 0) {
			error_handler(posix::latest_error());
			return {};
		}
		return s;
	}

	template<basic_range Path, typename ErrorHandler>
	inline optional<posix::status>
	try_get_file_status(
		Path&& path,
		ErrorHandler&& error_handler
	) {
		return view_on_stack_as_c_string(
			forward<Path>(path),
			[&](c_string_of_known_size<char> path) {
				return try_get_file_status(
					path,
					forward<ErrorHandler>(error_handler)
				);
			}
		);
	}

	inline posix::status get_file_status(handle<posix::file> file) {
		status s;
		int result = ::fstat(file.underlying(), &s);
		if(result != 0) {
			posix::unhandled(posix::latest_error());
		}
		return s;
	}

	inline posix::status get_file_status(any_c_string<char> auto path) {
		return try_get_file_status(path, posix::unhandled).get();
	}

}

inline posix::status handle_interface<posix::file>::get_status() const {
	return posix::get_file_status(handle<posix::file>{ underlying() });
}

inline posix::offset handle_interface<posix::file>::get_size() const {
	return get_status().size;
}