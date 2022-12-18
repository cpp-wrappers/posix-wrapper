#pragma once

#include "attribute.hpp"

extern "C" int pthread_mutexattr_settype(
	posix::mutex_attribute_handle_underlying* attr, int type
);

template<typename Handler>
void handle_interface<posix::mutex_attribute>::
try_set_type(posix::mutex_attribute_type type, Handler&& handler) {
	int result = pthread_mutexattr_settype(&underlying(), (int) type);
	if(result != 0) {
		handler(posix::error{ result });
	}
}