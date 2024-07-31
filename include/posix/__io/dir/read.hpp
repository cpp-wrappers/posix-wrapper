#pragma once

#include "./types.hpp"
#include "../../error.hpp"
#include "../../unhandled.hpp"

#include <expected.hpp>
#include <handle.hpp>

extern "C" struct dirent* readdir(struct DIR* dirp);

namespace posix {

	inline expected<handle<posix::dir_entry>, posix::error>
	try_read_dir(handle<posix::dir> dir_ptr) {
		auto prev_errno = posix::latest_error();

		auto result = (posix::dir_entry*)
			::readdir((struct DIR*) dir_ptr.underlying());

		auto _errno = posix::latest_error();

		if(result == nullptr && _errno.code() != prev_errno.code()) {
			return unexpected{ _errno };
		}
		return { result };
	}

	inline handle<posix::dir_entry> read_dir(handle<posix::dir> dir_ptr) {
		auto result = try_read_dir(dir_ptr);
		if(result.is_unexpected()) {
			posix::unhandled(result.get_unexpected());
		}
		return result.get_expected();
	}

}

inline handle<posix::dir_entry>
handle_interface<posix::dir>::read() const {
	return posix::read_dir(this->underlying());
}