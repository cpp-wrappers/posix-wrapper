#pragma once

#include "attribute.hpp"
#include "../../../error_handler.hpp"

#include <optional.hpp>

extern "C" int pthread_mutexattr_init(
	posix::mutex_attribute_handle_underlying* attr
);

namespace posix {

	template<typename Handler>
	optional<body<posix::mutex_attribute>>
	try_create_mutex_attribute(Handler&& handler) {
		posix::mutex_attribute_handle_underlying a;
		int result = ::pthread_mutexattr_init(&a);
		if(result != 0) {
			handler(posix::error{ result });
			return {};
		}

		return body<posix::mutex_attribute>{ a };
	}

	inline body<posix::mutex_attribute> create_mutex_attribute() {
		return try_create_mutex_attribute(
			[](posix::error err) { posix::error_handler(err); }
		).get();
	}

}