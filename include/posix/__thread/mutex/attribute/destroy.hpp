#pragma once

#include "./attribute.hpp"
#include "../../../error_handler.hpp"

#include <exchange.hpp>
#include <body.hpp>

extern "C" int pthread_mutexattr_destroy(
	posix::mutex_attribute_handle_underlying*
);

namespace posix {

	template<typename Handler>
	void try_destroy(handle<posix::mutex_attribute> m, Handler&& handler) {
		int result = pthread_mutexattr_destroy(&m.underlying());
		if(result != 0) {
			handler(posix::error{ result });
		}
	}

	inline void destroy(handle<posix::mutex_attribute> m) {
		try_destroy(m, posix::no_return_error_handler);
	}

}

template<>
constexpr void body<posix::mutex_attribute>::do_destroy() {
	posix::destroy(soul_handle_);
}