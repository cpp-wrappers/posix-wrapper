#pragma once

#include "./mutex.hpp"
#include "../../error.hpp"
#include "../../error_handler.hpp"

#include <optional.hpp>
#include <body.hpp>

extern "C" int pthread_mutex_init(
	posix::mutex_handle_underlying* mutex, const void* attr
);

namespace posix {

	template<typename Handler>
	optional<body<posix::mutex>> try_create_mutex(Handler&& handler) {
		posix::mutex_handle_underlying m;
		int result = ::pthread_mutex_init(&m, nullptr);
		if(result != 0) {
			handler(posix::error{ result });
			return {};
		}

		return body<posix::mutex>{ m };
	}

	inline body<posix::mutex> create_mutex() {
		optional<body<posix::mutex>> result = try_create_mutex(
			posix::no_return_error_handler
		);
		return move(result.value());
	}

}