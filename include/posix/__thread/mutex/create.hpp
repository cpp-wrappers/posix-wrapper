#pragma once

#include "./mutex.hpp"
#include "./attribute/attribute.hpp"
#include "../../error.hpp"
#include "../../unhandled.hpp"

#include <expected.hpp>
#include <body.hpp>

extern "C" int pthread_mutex_init(
	posix::mutex_handle_underlying* mutex,
	const posix::mutex_attribute_handle_underlying* attr
);

namespace posix {

	inline
	expected<body<posix::mutex>, posix::error>
	try_create_mutex(
		const body<posix::mutex_attribute>& attribute
	) {
		posix::mutex_handle_underlying m;
		int result = ::pthread_mutex_init(&m, &attribute->underlying());
		if(result != 0) {
			return { posix::error{ result } };
		}

		return body<posix::mutex>{ m };
	}

	inline body<posix::mutex> create_mutex(
		const body<posix::mutex_attribute>& attribute
	) {
		expected<body<posix::mutex>, posix::error> result = try_create_mutex(
			attribute
		);
		if(result.is_unexpected()) {
			posix::unhandled();
			__builtin_unreachable();
		}
		return move(result).get_expected();
	}

}