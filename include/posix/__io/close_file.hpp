#pragma once

#include "./file.hpp"

#include <body.hpp>
#include <exchange.hpp>

extern "C" int close(int fd);

namespace posix {

	template<typename ErrorHandler>
	inline void try_close(
		handle<posix::file> fd, ErrorHandler unexpected_handler
	) {
		int result = ::close(fd.underlying());
		if(result == -1) {
			unexpected_handler(posix::latest_error());
		}
	}

	inline void close(handle<posix::file> fd) {
		posix::try_close(fd, posix::unhandled);
	}

}

template<>
inline void body<posix::file>::do_destroy() {
	posix::close(this->soul_handle_);
}