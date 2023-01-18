#pragma once

#include "attribute.hpp"
#include "../../../unhandled.hpp"

#include <expected.hpp>

extern "C" int pthread_mutexattr_init(
	posix::mutex_attribute_handle_underlying* attr
);

namespace posix {

	inline
	expected<body<posix::mutex_attribute>, posix::error>
	try_create_mutex_attribute() {
		posix::mutex_attribute_handle_underlying a;
		int result = ::pthread_mutexattr_init(&a);
		if(result != 0) {
			return posix::error{ result };
		}

		return body<posix::mutex_attribute>{ a };
	}

	inline body<posix::mutex_attribute> create_mutex_attribute() {
		expected<body<posix::mutex_attribute>, posix::error> result
			= try_create_mutex_attribute();
		if(result.is_unexpected()) {
			posix::unhandled(result.get_unexpected());
		}
		return move(result).get_expected();
	}

}