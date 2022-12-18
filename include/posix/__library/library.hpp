#pragma once

#include <body.hpp>

namespace posix {
	struct library;
}

template<>
struct handle_underlying_t<posix::library> {
	using type = void*;
	static constexpr type invalid = nullptr;
};

template<>
struct handle_interface<posix::library> :
	handle_interface_base<posix::library>
{
};