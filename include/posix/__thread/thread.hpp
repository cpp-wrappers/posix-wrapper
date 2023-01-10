#pragma once

#include <integer.hpp>
#include <handle.hpp>
#include <optional.hpp>

namespace posix {

	struct thread;

	using thread_handle_underlying =
	#if __MINGW64__
		uint64;
	#elif __linux__
		unsigned long int;
	#else
		static_assert(false);
	#endif

	inline handle<posix::thread> self();

}

template<>
struct handle_underlying_t<posix::thread> {
	using type = posix::thread_handle_underlying;
	static constexpr type invalid = type(-1);
};

template<>
struct handle_interface<posix::thread> : handle_interface_base<posix::thread> {
	
};