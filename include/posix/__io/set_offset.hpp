#pragma once

#include "./file.hpp"
#include "./offset.hpp"

#include <integer.hpp>

namespace posix {

	enum class __seek {
		#if __MINGW32__ || __gnu_linux__
		set = 0,
		cur = 1,
		end = 2
		#else
		static_assert(false);
		#endif
	};
}

extern "C" posix::offset
lseek(int fd, posix::offset o, int whence);

posix::offset handle_interface<posix::file>::
set_offset(posix::offset o) const {
	return ::lseek(underlying(), o, (int) posix::__seek::set);
}

posix::offset handle_interface<posix::file>::
set_offset_relative_to_current(posix::offset o) const {
	return ::lseek(underlying(), o, (int) posix::__seek::cur);
}

posix::offset handle_interface<posix::file>::
set_offset_relative_to_end(posix::offset o) const {
	return ::lseek(underlying(), o, (int) posix::__seek::end);
}

posix::offset handle_interface<posix::file>::
set_offset_to_end() const {
	return ::lseek(underlying(), 0, (int) posix::__seek::end);
}