#pragma once

#include "../error.hpp"
#include "../error_handler.hpp"
#include "./file_access_mode.hpp"
#include "./move_offset.hpp"

#include <c_string.hpp>
#include <range.hpp>
#include <optional.hpp>
#include <expected.hpp>
#include <handle.hpp>

extern "C" nint write(int fd, const void* buf, nuint nbytes);
extern "C" nint read(int fd, void *buf, nuint nbytes);

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
		Range&& range, ErrorHandler error_handler
	) const {
		nint result = ::read(
			underlying(),
			&*range_iterator(range),
			range_size(range) * sizeof(range_element_type<Range>)
		);
		if(result == -1) {
			error_handler(posix::latest_error());
			__builtin_unreachable();
		}
		return result;
	}

	template<contiguous_range Range>
	nuint read_to(Range&& range) const {
		return try_read_to(
			forward<Range>(range),
			[](posix::error e) { posix::error_handler(e); }
		);
	}

	template<contiguous_range Range, typename ErrorHandler>
	nuint try_write_from(
		Range&& range, nuint size, ErrorHandler&& error_handler
	) const {
		nint result = ::write(
			underlying(),
			&*range_iterator(range),
			size * sizeof(range_element_type<Range>)
		);
		if(result == -1) {
			error_handler(posix::latest_error());
			__builtin_unreachable();
		}
		return result;
	}

	template<contiguous_range Range, typename ErrorHandler>
	nuint try_write_from(
		Range&& range, ErrorHandler&& error_handler
	) const {
		auto size = range_size(range);
		return try_write_from(
			forward<Range>(range),
			size,
			forward<ErrorHandler>(error_handler)
		);
	}

	template<contiguous_range Range>
	nuint write_from(Range&& range, nuint size) const {
		return try_write_from(
			forward<Range>(range), size,
			[](posix::error e) { posix::error_handler(e); }
		);
	}

	template<contiguous_range Range>
	nuint write_from(Range&& range) const {
		nuint size = range_size(range);
		return write_from(forward<Range>(range), size);
	}

	posix::offset set_offset(posix::offset o) const {
		return ::lseek(underlying(), o, (int) posix::__seek::set);
	}

	posix::offset set_offset_relative_to_current(posix::offset o) const {
		return ::lseek(underlying(), o, (int) posix::__seek::cur);
	}

	posix::offset set_offset_relative_to_end(posix::offset o) const {
		return ::lseek(underlying(), o, (int) posix::__seek::end);
	}

	posix::offset set_offset_to_end() const {
		return ::lseek(underlying(), 0, (int) posix::__seek::end);
	}

};