#pragma once

#include "./file_descriptor.hpp"
#include "./close_file.hpp"

namespace posix {

class own_file {
	file_descriptor fd{ -1 };
public:

	own_file() = default;
	own_file(file_descriptor file) : fd{ file } {}

	own_file(const own_file&) = delete;
	own_file(own_file&&) = delete;

	const file_descriptor* operator ->() const { return &fd; }
	      file_descriptor* operator ->()       { return &fd; }

	~own_file() {
		if(fd.number_ != -1) {
			posix::close_file(fd);
		}
	}
};

}