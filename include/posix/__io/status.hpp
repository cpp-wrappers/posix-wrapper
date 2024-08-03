#pragma once

#include "./offset.hpp"
#include <integer.hpp>
#include <enum_flags.hpp>

namespace posix {

enum class file_mode : unsigned short {
#if __WIN64
	block = 0x3000,
	character = 0x2000,
	fifo = 0x1000,
	regular = 0x8000,
	dir = 0x4000,
	// link = isn't supported,
	// socket = isn't supported,

	read = 0x0100,
	write = 0x0080,
	execute = 0x0040,
#else
	block = 0060000,
	character = 0020000,
	fifo = 0010000,
	regular = 0100000,
	dir = 0040000,
	link = 0120000,
	socket = 0140000,

	read = 0400,
	write = 0200,
	execute = 0100,
#endif

	user_rw = read | write,
	user_rwx = read | write | execute,
	group_rw = (read | write) >> 3,
	group_rwx = (read | write | execute) >> 3,
	others_r = (read) >> 6,
	others_rx = (read | execute) >> 6
};

using file_modes = enum_flags<file_mode>;

struct status {
#if __WIN64
	using dev_t = unsigned int;
	using time_t = int64;
	using ino_t = unsigned short;
	using mode_t = short;

	dev_t device_id;
	ino_t id;
	file_modes mode;
	short hard_links_count;
	short user_id;
	short group_id;
	dev_t device_id_character_or_block_special;
	posix::offset size;
	time_t last_access_time;
	time_t last_modification_time;
	time_t last_status_change;
#elif __linux__
	unsigned long device_id;
	unsigned long id;
	unsigned long hard_links_count;
	file_modes mode;
	unsigned int user_id;
	unsigned int group_id;
	int __pad;
	unsigned long device_id_character_or_block_special;
	posix::offset size;
	posix::offset block_size;
	long blocks;
	long last_access_time;
	long last_access_time_nanos;
	long last_modification_time;
	long last_modification_time_nanos;
	long last_status_change;
	long last_status_change_nanos;
	long glibc_reserved[3];
#endif

	bool is_dir() const {
		return mode.get(file_mode::dir);
	}

	bool is_regular() const {
		return mode.get(file_mode::regular);
	}
};

}