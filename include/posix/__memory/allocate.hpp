#pragma once

#include "./memory.hpp"
#include "../unhandled.hpp"

extern "C" [[gnu::malloc]] [[gnu::alloc_size(1)]] void* malloc(nuint size);

namespace posix {

	template<typename Type, typename ErrorHandler>
	inline span<Type>
	try_allocate_raw(
		nuint elements_number, ErrorHandler&& error_handler
	) {
		void* ptr = malloc(elements_number * sizeof(Type));
		if(ptr == nullptr) {
			error_handler(posix::latest_error());
			__builtin_unreachable();
		}
		return { (Type*) ptr, elements_number };
	}

	template<typename Type>
	inline span<Type>
	allocate_raw(nuint elements_number) {
		return try_allocate_raw<Type>(
			elements_number, posix::unhandled
		);
	}

	template<typename Type, typename ErrorHandler>
	inline memory<Type>
	try_allocate(
		nuint elements_number, ErrorHandler&& error_handler
	) {
		span<Type> s = try_allocate_raw<Type>(
			elements_number,
			error_handler
		);
		return { s.iterator(), s.size() };
	}

	template<typename Type = uint1a>
	inline memory<Type>
	allocate(nuint elements_number) {
		return try_allocate<Type>(
			elements_number, posix::unhandled
		);
	}

}