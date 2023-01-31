#pragma once

#include "./file_access_mode.hpp"
#include "./offset.hpp"
#include "./status.hpp"
#include "../error.hpp"
#include "../unhandled.hpp"

#include <c_string.hpp>
#include <range.hpp>
#include <optional.hpp>
#include <expected.hpp>
#include <handle.hpp>

namespace posix {
	struct file;
}

template<>
struct handle_underlying_t<posix::file> {
	using type = int32;
	static constexpr type invalid = -1;
};

template<>
struct handle_interface<posix::file> : handle_interface_base<posix::file> {

	template<contiguous_range Range, typename ErrorHandler>
	nuint try_read_to(
		Range&& range, ErrorHandler unexpected_handler
	) const;

	template<contiguous_range Range>
	nuint read_to(Range&& range) const;

	template<contiguous_range Range, typename ErrorHandler>
	nuint try_write_from(
		Range&& range, nuint size, ErrorHandler&& unexpected_handler
	) const;

	template<contiguous_range Range, typename ErrorHandler>
	nuint try_write_from(
		Range&& range, ErrorHandler&& unexpected_handler
	) const;

	template<contiguous_range Range>
	nuint write_from(Range&& range, nuint size) const;

	template<contiguous_range Range>
	nuint write_from(Range&& range) const;

	inline posix::offset
	set_offset(posix::offset o) const;

	inline posix::offset
	set_offset_relative_to_current(posix::offset o) const;

	inline posix::offset
	set_offset_relative_to_end(posix::offset o) const;

	inline posix::offset
	set_offset_to_end() const;

	inline posix::offset get_size() const;

	inline posix::status get_status() const;

};