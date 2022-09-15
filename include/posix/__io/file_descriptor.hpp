#pragma once

#include "../error.hpp"
#include "../error_handler.hpp"
#include "./file_access_mode.hpp"
#include "./move_offset.hpp"

#include <c_string.hpp>
#include <range.hpp>
#include <optional.hpp>
#include <expected.hpp>

extern "C" nint write(int fd, const void* buf, nuint nbytes);
extern "C" nint read(int fd, void *buf, nuint nbytes);

namespace posix {

struct file_descriptor {
	int number_;

	template<contiguous_range Range, typename ErrorHandler>
	nuint try_read_to(Range&& range, ErrorHandler error_handler) const {
		nint result = ::read(
			number_,
			&*range_iterator(range),
			range_size(range) * sizeof(range_element_type<Range>)
		);
		if(result == -1) {
			error_handler(posix::latest_error());
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
			number_,
			&*range_iterator(range),
			size * sizeof(range_element_type<Range>)
		);
		if(result == -1) {
			error_handler(posix::latest_error());
		}
		return result;
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

	offset set_offset(posix::offset o) const {
		return ::lseek(number_, o, (int) posix::__seek::set);
	}

	offset set_offset_relative_to_current(posix::offset o) const {
		return ::lseek(number_, o, (int) posix::__seek::cur);
	}

	offset set_offset_relative_to_end(posix::offset o) const {
		return ::lseek(number_, o, (int) posix::__seek::end);
	}

	offset set_offset_to_end() const {
		return ::lseek(number_, 0, (int) posix::__seek::end);
	}

};

}