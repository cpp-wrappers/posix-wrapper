#pragma once

#include "./thread.hpp"
#include "../error_handler.hpp"

#include <tuple.hpp>

int pthread_create(
	void* thread, const void* attr, void *(*start_routine)(void *), void* arg
);

namespace posix {

template<typename Function, typename Arg>
thread try_create_thread(Function func, Arg&& arg) {
	thread th;

	int result = pthread_create(
		&th.thread_t_,
		nullptr,
		func,
		&arg
	);

	if(result != 0) {
		posix::error_handler(posix::error{ result });
		return {};
	}

	return th;
}

}