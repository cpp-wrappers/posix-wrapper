#pragma once

#include "../../__internal/unexpected_handler.hpp"

#include <handle.hpp>
#include <body.hpp>
#include <optional.hpp>
#include <array.hpp>

namespace posix {

	struct mutex;

	using mutex_handle_underlying = 
	#if __MINGW32__
		int64;
	#elif __linux__
		array<char, 40>;
	#else
		static_assert(false)
	#endif

}

template<>
struct handle_underlying_t<posix::mutex> {
	using type = posix::mutex_handle_underlying;
	static constexpr type invalid =
		#if __MINGW32__
			type(-1);
		#elif __linux__
			posix::mutex_handle_underlying{};
		#else
			static_assert(false)
		#endif
};

template<>
struct handle_interface<posix::mutex> : handle_interface_base<posix::mutex> {

	template<typename Handler>
	void try_lock(Handler&& handler);

	template<typename Handler>
	void try_unlock(Handler&& handler);

	void lock() {
		try_lock([](posix::error err) { posix::unexpected_handler(err); });
	}

	void unlock() {
		try_unlock([](posix::error err) { posix::unexpected_handler(err); });
	}

};