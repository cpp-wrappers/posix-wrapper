#pragma once

#include "./type.hpp"
#include "../../../unhandled.hpp"

#include <body.hpp>
#include <integer.hpp>
#include <array.hpp>

namespace posix {

	struct mutex_attribute;

	#if __linux__
	struct mutex_attribute_storage : array<char, 4> {
		constexpr mutex_attribute_storage() :
			array{ char(-1), char(-1), char(-1), char(-1) }
		{}
	};
	#endif

	using mutex_attribute_handle_underlying = 
#if __MINGW32__
		unsigned int;
#elif __linux__
		mutex_attribute_storage;
#else
	static_assert(false)
#endif

};

template<>
struct handle_underlying_t<posix::mutex_attribute> {
	using type = posix::mutex_attribute_handle_underlying;
	static constexpr type invalid =
	#if __MINGW32__
		type( -1 );
	#elif __linux__
		{};
	#endif
};

template<>
struct handle_interface<posix::mutex_attribute>
: handle_interface_base<posix::mutex_attribute>
{

	template<typename Handler>
	void try_set_type(posix::mutex_attribute_type, Handler&&);

	void set_type(posix::mutex_attribute_type type) {
		try_set_type(type, posix::unhandled);
	}

};