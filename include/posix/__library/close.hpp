#pragma once

#include "./handle.hpp"

extern "C" int dlclose(void *handle);

template<>
inline void body<posix::library>::do_destroy() {
	dlclose(soul_handle_.underlying());
}