#pragma once

#include "../../error_handler.hpp"

#include <handle.hpp>
#include <body.hpp>
#include <optional.hpp>

namespace posix {

	struct mutex;

#if __MINGW64__
	using mutex_handle_underlying = int64;
#else
	static_assert(false)
#endif

}

template<>
struct handle_underlying_t<posix::mutex> {
	using type = posix::mutex_handle_underlying;
	static constexpr type invalid = type(-1);
};

template<>
struct handle_interface<posix::mutex> : handle_interface_base<posix::mutex> {

	template<typename Handler>
	void try_lock(Handler&& handler);

	template<typename Handler>
	void try_unlock(Handler&& handler);

	void lock() {
		try_lock(posix::no_return_error_handler);
	}

	void unlock() {
		try_unlock(posix::no_return_error_handler);
	}

};