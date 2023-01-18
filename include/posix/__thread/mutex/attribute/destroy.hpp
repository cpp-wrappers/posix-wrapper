#pragma once

#include "./attribute.hpp"
#include "../../../unhandled.hpp"

#include <exchange.hpp>
#include <body.hpp>

extern "C" int pthread_mutexattr_destroy(
	posix::mutex_attribute_handle_underlying*
);

namespace posix {

	inline optional<posix::error>
	try_destroy(handle<posix::mutex_attribute> m) {
		int result = pthread_mutexattr_destroy(&m.underlying());
		if(result != 0) {
			return posix::error{ result };
		}
		return {};
	}

	inline void destroy(handle<posix::mutex_attribute> m) {
		optional<posix::error> result = try_destroy(m);
		if(result.has_value()) {
			posix::unhandled(result.get());
		}
	}

}

template<>
inline void body<posix::mutex_attribute>::do_destroy() {
	posix::destroy(soul_handle_);
}