#pragma once

#include "../../unhandled.hpp"

#include <handle.hpp>
#include <body.hpp>
#include <optional.hpp>
#include <array.hpp>
#include <storage.hpp>

namespace posix {

	struct mutex;

	#if __linux__
	struct mutex_storage : array<char, 40> {
		constexpr mutex_storage() {}
	};
	#endif

	using mutex_handle_underlying = 
	#if __MINGW32__
		int64;
	#elif __linux__
		mutex_storage;
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

	void lock() { try_lock(posix::unhandled); }
	void unlock() { try_unlock(posix::unhandled); }

};