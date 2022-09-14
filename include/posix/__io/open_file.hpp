#pragma once

#include "./file.hpp"

#include <enum_flags.hpp>

extern "C" int open(const char *path, int oflag, ... );

namespace posix {

template<typename ErrorHandler>
inline expected<own_file, posix::error> try_open_file(
	c_string_of_unknown_size name, file_access_modes modes
) {
	int fd = open(name.iterator(), (int) modes);
	if(fd == -1) {
		return posix::latest_error();
	}
	return own_file{ * (file*)(nuint) fd };
}

inline own_file open_file(any_c_string auto name, file_access_modes modes) {
	int fd = open(name.iterator(), (int) modes);
	if(fd == -1) {
		posix::error_handler(posix::latest_error());
	}
	return own_file{ file{ fd } };
}

}