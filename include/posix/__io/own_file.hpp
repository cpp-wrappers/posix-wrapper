#pragma once

#include "./file_descriptor.hpp"
#include "./close_file.hpp"

namespace posix {

class own_file {
	file_descriptor fd;
public:

	own_file(file_descriptor file) : fd{ file } {}

	const file_descriptor* operator ->() const { return &fd; }
	      file_descriptor* operator ->()       { return &fd; }

	~own_file() {
		// file descriptor is always valid, don't check for EOF
		posix::close_file(fd);
	}
};

}