#pragma once

#include "./mutex.hpp"
#include "../../error.hpp"
#include "../../__internal/unexpected_handler.hpp"

#include <exchange.hpp>
#include <body.hpp>

extern "C" int pthread_mutex_destroy(posix::mutex_handle_underlying*);

namespace posix {

	template<typename Handler>
	void try_destroy(handle<posix::mutex> m, Handler&& handler) {
		int result = pthread_mutex_destroy(&m.underlying());
		if(result != 0) {
			handler(posix::error{ result });
		}
	}

	inline void destroy(handle<posix::mutex> m) {
		try_destroy(
			m,
			[](posix::error err) { posix::unexpected_handler(err); }
		);
	}

}

template<>
inline void body<posix::mutex>::do_destroy() {
	posix::destroy(soul_handle_);
}