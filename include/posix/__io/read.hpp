#pragma once

#include "./file.hpp"

extern "C" nint read(int fd, void *buf, nuint nbytes);

template<contiguous_range Range, typename ErrorHandler>
nuint handle_interface<posix::file>::try_read_to(
	Range&& range, ErrorHandler unexpected_handler
) const {
	nint result = ::read(
		underlying(),
		&*range_iterator(range),
		range_size(range) * sizeof(range_element_type<Range>)
	);
	if(result == -1) {
		unexpected_handler(posix::latest_error());
		__builtin_unreachable();
	}
	return result;
}

template<contiguous_range Range>
nuint handle_interface<posix::file>::read_to(Range&& range) const {
	return try_read_to(::forward<Range>(range), posix::unhandled);
}