#pragma once

#include "./thread.hpp"
#include "../error_handler.hpp"

#include <tuple.hpp>

extern "C" int pthread_create(
	posix::thread_handle_underlying* thread,
	const void* attr, void* (*start_routine)(void*), void* arg
);

namespace posix {

	template<typename Function, typename Arg, typename ErrorHandler>
	optional<handle<thread>> try_create_thread(
		Function function, Arg* arg_ptr, ErrorHandler&& error_handler
	) {
		thread_handle_underlying thread_ptr;

		int result = ::pthread_create(
			&thread_ptr,
			nullptr,
			function,
			(void*) arg_ptr
		);

		if(result != 0) {
			error_handler(posix::error{ result });
			return {};
		}

		return handle<thread>{ thread_ptr };
	}

	template<typename Function, typename ErrorHandler>
	optional<handle<thread>> try_create_thread(
		Function function, ErrorHandler&& error_handler
	) {
		return try_create_thread(
			forward<Function>(function),
			(void*) nullptr,
			forward<ErrorHandler>(error_handler)
		);
	}

	template<typename Function, typename Arg>
	handle<thread> create_thread(Function func, Arg& arg) {
		return try_create_thread(
			forward<Function>(func),
			arg,
			posix::no_return_error_handler
		).get();
	}

	template<typename Function>
	handle<thread> create_thread(Function func) {
		return try_create_thread(
			forward<Function>(func),
			posix::no_return_error_handler
		).get();
	}

}