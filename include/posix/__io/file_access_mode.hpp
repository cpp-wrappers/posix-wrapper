#pragma once

#include <enum_flags.hpp>

namespace posix {

enum class file_access_mode {
	#ifdef __MINGW64__
	read       = 0x0000,
	write      = 0x0001,
	read_write = 0x0002,
	append     = 0x0008,
	create     = 0x0100,
	trunc      = 0x0200,
	exclusive  = 0x0400,
	text       = 0x4000,
	binary     = 0x8000
	#else
	static_assert(false);
	#endif
};

using file_access_modes = enum_flags<file_access_mode>;

}