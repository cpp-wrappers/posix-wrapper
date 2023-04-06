#pragma once

#include <enum_flags.hpp>

namespace posix {

enum class file_access_mode {
	#if __MINGW32__
	read       = 0x0000,
	write      = 0x0001,
	read_write = 0x0002,
	append     = 0x0008,
	create     = 0x0100,
	trunc      = 0x0200,
	exclusive  = 0x0400,
	text       = 0x4000,
	binary     = 0x8000,
	#elif __gnu_linux__

	binary     = 00000,
	read       = 00000,
	write      = 00001,
	read_write = 00002,
	create     = 00100,
	exclusive  = 00200,
	trunc      = 01000,
	append     = 02000,
	text       = 04000,

	#else
	static_assert(false);
	#endif

	binary_read = binary | read
};

using file_access_modes = enum_flags<file_access_mode>;

}