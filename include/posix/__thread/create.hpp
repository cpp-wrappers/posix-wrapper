#pragma once

#include "./thread.hpp"
#include "../unhandled.hpp"

#include <tuple.hpp>
#include <expected.hpp>

extern "C" int pthread_create(
	posix::thread_handle_underlying* thread,
	const void* attr, void* (*start_routine)(void*), void* arg
);

namespace posix {

	template<typename Function, typename Arg>
	expected<handle<thread>, posix::error> try_create_thread(
		Function&& function, Arg& arg
	) {
		thread_handle_underlying thread_ptr;

		int result = ::pthread_create(
			&thread_ptr,
			nullptr,
			function,
			(void*) &arg
		);

		if(result != 0) {
			return { posix::error{ result } };
		}

		return handle<thread>{ thread_ptr };
	}

	template<typename Function, typename Arg>
	handle<thread> create_thread(
		Function&& function, Arg& arg
	) {
		expected<handle<thread>, posix::error> result = try_create_thread(
			forward<Function>(function), arg
		);
		if(result.is_unexpected()) {
			posix::unhandled(result.get_unexpected());
		}
		return move(result).get_expected();
	}

	template<typename Function>
	handle<thread> create_thread(Function&& func) {
		int dummy;
		return create_thread(
			forward<Function>(func), dummy	
		);
	}

}