#pragma once

#include "./handle.hpp"
#include "../unhandled.hpp"

#include <optional.hpp>
#include <c_string.hpp>

extern "C" void* dlopen(const char* file, int flag);

namespace posix {

	enum class open_library_flag {
		lazy,
		now
	};

	inline optional<handle<posix::library>>
	try_open_library(
		any_c_string auto file,
		open_library_flag flag = open_library_flag::now
	) {
		void* result = dlopen(file.iterator(), (int) flag);
		if(result == nullptr) {
			return {};
		}
		return { result };
	}

	inline handle<posix::library>
	open_library(
		any_c_string auto file,
		open_library_flag flag = open_library_flag::now
	) {
		return try_open_library(file, flag)
			.if_has_no_value(posix::unhandled)
			.get();
	}

}