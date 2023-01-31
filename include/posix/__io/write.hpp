#pragma once

#include "./file.hpp"
#include <integer.hpp>

#include <range.hpp>

extern "C" nint write(int fd, const void* buf, nuint nbytes);

template<contiguous_range Range, typename ErrorHandler>
nuint handle_interface<posix::file>::try_write_from(
	Range&& range, nuint size, ErrorHandler&& unexpected_handler
) const {
	nint result = ::write(
		underlying(),
		&*range_iterator(range),
		size * sizeof(range_element_type<Range>)
	);
	if(result == -1) {
		unexpected_handler(posix::latest_error());
		__builtin_unreachable();
	}
	return result;
}

template<contiguous_range Range, typename ErrorHandler>
nuint handle_interface<posix::file>::try_write_from(
	Range&& range, ErrorHandler&& unexpected_handler
) const {
	auto size = range_size(range);
	return try_write_from(
		forward<Range>(range),
		size,
		forward<ErrorHandler>(unexpected_handler)
	);
}

template<contiguous_range Range>
nuint handle_interface<posix::file>::write_from(
	Range&& range, nuint size
) const {
	return try_write_from(forward<Range>(range), size, posix::unhandled);
}

template<contiguous_range Range>
nuint handle_interface<posix::file>::write_from(
	Range&& range
) const {
	nuint size = range_size(range);
	return write_from(forward<Range>(range), size);
}