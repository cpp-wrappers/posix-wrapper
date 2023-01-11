#pragma once

#include "./handle.hpp"
#include "../__internal/unexpected_handler.hpp"

extern "C" void* dlsym(void* handle, const char* name);

void*
handle_interface<posix::library>::
get_symbol_address(any_c_string auto name) const {
	void* result = dlsym(underlying(), name.iterator());
	if(result == nullptr) {
		posix::unexpected_handler();
	}
	return result;
}