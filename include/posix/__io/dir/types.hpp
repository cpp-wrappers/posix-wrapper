#pragma once

#include <integer.hpp>
#include <handle.hpp>
#include <c_string.hpp>
#include <span.hpp>

namespace posix {

#if __WIN64

	struct _finddata64i32_t {
		unsigned attrib;
		int64 time_create;
		int64 time_access;
		int64 time_write;
		unsigned long size;
		char name[260];
	};

	struct dir_entry {
		long i_node_;
		unsigned short record_length_;
		unsigned short name_length_;
		char name_[260];
	};

	struct dir {
		posix::_finddata64i32_t dd_dta;
		struct posix::dir_entry dd_dir;
		int64 dd_handle;
		int dd_stat;
		char dd_name[1];
	};

#endif

}

template<>
struct handle_underlying_t<posix::dir> {
	using type = posix::dir*;
	static constexpr type invalid = nullptr;
};

template<>
struct handle_interface<posix::dir> : handle_interface_base<posix::dir> {
	handle<posix::dir_entry> read() const;
};

template<>
struct handle_underlying_t<posix::dir_entry> {
	using type = posix::dir_entry*;
	static constexpr type invalid = nullptr;
};

template<>
struct handle_interface<posix::dir_entry> :
	handle_interface_base<posix::dir_entry>
{
	auto name() const {
		return c_string_view {
			this->underlying()->name_,
			this->underlying()->name_length_
		};
	}
};