#pragma once

#include "../error.hpp"
#include "../error_handler.hpp"
#include "./file_access_mode.hpp"

#include <c_string.hpp>
#include <range.hpp>
#include <optional.hpp>
#include <expected.hpp>

extern "C" int close(int fd);
extern "C" nint write(int fd, const void* buf, nuint nbytes);
extern "C" nint read(int fd, void *buf, nuint nbytes);

namespace posix {

struct file {
	int fd;

	template<contiguous_range Range, typename ErrorHandler>
	nuint try_read_to(Range&& range, ErrorHandler error_handler) const {
		nint result = ::read(
			fd,
			range_iterator(range),
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
			fd,
			range_iterator(range),
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

};

class own_file {
	file file_;
public:

	own_file(file file) : file_{ file } {}

	const file* operator ->() const { return &file_; }
	      file* operator ->()       { return &file_; }

	~own_file() {
		// file descriptor is always valid, don't check for EOF
		::close(file_.fd);
	}
};

}