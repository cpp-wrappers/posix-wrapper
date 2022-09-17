#pragma once

#include "./file_descriptor.hpp"

extern "C" int close(int fd);

namespace posix {

	template<typename ErrorHandler>
	inline void try_close_file(
		posix::file_descriptor fd, ErrorHandler error_handler
	) {
		int result = ::close(fd.number_);
		if(result == -1) {
			error_handler(posix::latest_error());
		}
	}

	inline void close_file(posix::file_descriptor fd) {
		posix::try_close_file(fd, posix::error_handler);
	}

}