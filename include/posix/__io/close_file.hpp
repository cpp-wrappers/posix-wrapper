#pragma once

#include "./file_descriptor.hpp"

extern "C" int close(int fd);

namespace posix {

	inline void close_file(posix::file_descriptor fd) {
		::close(fd.number_);
	}

}