#pragma once

#include "./offset.hpp"
#include <integer.hpp>

namespace posix {

	struct status {
	#if __WIN64
		using dev_t = unsigned int;
		using time_t = int64;
		using ino_t = unsigned short;
		using mode_t = short;

		dev_t device_id;
		ino_t id;
		mode_t mode;
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
		unsigned int mode;
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
	};
}