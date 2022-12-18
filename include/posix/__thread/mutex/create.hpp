#pragma once

#include "./mutex.hpp"
#include "./attribute/attribute.hpp"
#include "../../error.hpp"
#include "../../error_handler.hpp"

#include <optional.hpp>
#include <body.hpp>

extern "C" int pthread_mutex_init(
	posix::mutex_handle_underlying* mutex,
	const posix::mutex_attribute_handle_underlying* attr
);

namespace posix {

	template<typename Handler>
	optional<body<posix::mutex>> try_create_mutex(
		const body<posix::mutex_attribute>& attribute,
		Handler&& handler
	) {
		posix::mutex_handle_underlying m;
		int result = ::pthread_mutex_init(&m, &attribute->underlying());
		if(result != 0) {
			handler(posix::error{ result });
			return {};
		}

		return body<posix::mutex>{ m };
	}

	inline body<posix::mutex> create_mutex(
		const body<posix::mutex_attribute>& attribute
	) {
		return try_create_mutex(
			attribute,
			posix::no_return_error_handler
		).get();
	}

}