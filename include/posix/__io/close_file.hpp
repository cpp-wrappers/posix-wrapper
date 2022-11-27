#pragma once

#include "./file_descriptor.hpp"

#include <body.hpp>
#include <exchange.hpp>

extern "C" int close(int fd);

namespace posix {

	template<typename ErrorHandler>
	inline void try_close(
		handle<posix::file> fd, ErrorHandler error_handler
	) {
		int result = ::close(fd.underlying());
		if(result == -1) {
			error_handler(posix::latest_error());
		}
	}

	inline void close(handle<posix::file> fd) {
		posix::try_close(fd, posix::error_handler);
	}

}

template<>
constexpr void body<posix::file>::do_destroy() {
	posix::close(this->soul_handle_);
}