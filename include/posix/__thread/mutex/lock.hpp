#pragma once

#include "./mutex.hpp"

#include "../../error.hpp"

extern "C" int pthread_mutex_lock(posix::mutex_handle_underlying* mutex);
extern "C" int pthread_mutex_trylock(posix::mutex_handle_underlying* mutex);
extern "C" int pthread_mutex_unlock(posix::mutex_handle_underlying* mutex);

template<typename Handler>
void handle_interface<posix::mutex>::try_lock(Handler&& handler) {
	int result = pthread_mutex_lock(&underlying());
	if(result != 0) {
		handler(posix::error{ result });
	}
}

template<typename Handler>
void handle_interface<posix::mutex>::try_unlock(Handler&& handler) {
	int result = pthread_mutex_unlock(&underlying());
	if(result != 0) {
		handler(posix::error{ result });
	}
}