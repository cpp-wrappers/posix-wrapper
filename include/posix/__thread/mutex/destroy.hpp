#pragma once

#include "./mutex.hpp"
#include "../../error.hpp"
#include "../../unhandled.hpp"

#include <exchange.hpp>
#include <body.hpp>

extern "C" int pthread_mutex_destroy(posix::mutex_handle_underlying*);

namespace posix {

	inline optional<posix::error> try_destroy(handle<posix::mutex> m) {
		int result = pthread_mutex_destroy(&m.underlying());
		if(result != 0) {
			return posix::error{ result };
		}
		return {};
	}

	inline void destroy(handle<posix::mutex> m) {
		try_destroy(m).if_has_value([](posix::error err) {
			posix::unhandled(err);
			__builtin_unreachable();
		});
	}

}

template<>
inline void body<posix::mutex>::do_destroy() {
	posix::destroy(soul_handle_);
}