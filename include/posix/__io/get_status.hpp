#pragma once

#include "./file.hpp"
#include "./status.hpp"
#include "../error.hpp"
#include "../unhandled.hpp"

extern "C" int fstat(int fildes, posix::status* buf);

namespace posix {

	inline posix::status get_file_status(handle<posix::file> file) {
		status s;
		int result = fstat(file.underlying(), &s);
		if(result != 0) {
			posix::unhandled(posix::latest_error());
		}
		return s;
	}

}

inline posix::status handle_interface<posix::file>::get_status() const {
	return posix::get_file_status(handle<posix::file>{ underlying() });
}

inline posix::offset handle_interface<posix::file>::get_size() const {
	return get_status().size;
}