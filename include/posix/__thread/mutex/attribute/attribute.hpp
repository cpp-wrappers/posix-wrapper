#pragma once

#include "./type.hpp"
#include "../../../error_handler.hpp"

#include <body.hpp>
#include <integer.hpp>

namespace posix {

	struct mutex_attribute;

	using mutex_attribute_handle_underlying = 
#if __MINGW64__
		unsigned int;
#elif __linux__
		uint_of_atoms<4>;
#else
	static_assert(false)
#endif

};

template<>
struct handle_underlying_t<posix::mutex_attribute> {
	using type = posix::mutex_attribute_handle_underlying;
	static constexpr type invalid = -1;
};

template<>
struct handle_interface<posix::mutex_attribute>
: handle_interface_base<posix::mutex_attribute>
{

	template<typename Handler>
	void try_set_type(posix::mutex_attribute_type, Handler&&);

	void set_type(posix::mutex_attribute_type type) {
		try_set_type(
			type,
			[](posix::error err) { posix::error_handler(err); }
		);
	}

};