#pragma once

#include "./memory.hpp"
#include "../unhandled.hpp"

extern "C"
	[[gnu::malloc]]
	[[gnu::alloc_size(2, 1)]]
	void *calloc(nuint elements_number, nuint element_size);

namespace posix {

	template<typename Type, typename ErrorHandler>
	inline span<Type>
	try_allocate_raw_zeroed(
		nuint elements_number, ErrorHandler&& unexpected_handler
	) {
		void* ptr = calloc(elements_number, sizeof(Type));
		if(ptr == nullptr) {
			unexpected_handler(posix::latest_error());
			__builtin_unreachable();
		}
		return { (Type*) ptr, elements_number };
	}

	template<typename Type, typename ErrorHandler>
	inline memory<Type>
	try_allocate_zeroed(
		nuint elements_number, ErrorHandler&& unexpected_handler
	) {
		span<Type> s = try_allocate_raw_zeroed<Type>(
			elements_number, unexpected_handler
		);
		return { s.iterator(), s.size() };
	}

	template<typename Type>
	inline span<Type>
	allocate_raw_zeroed(nuint elements_number) {
		return try_allocate_raw_zeroed<Type>(
			elements_number, posix::unhandled
		);
	}

	template<typename Type = uint1a>
	inline memory<Type>
	allocate_zeroed(nuint elements_number) {
		return try_allocate_zeroed<Type>(
			elements_number, posix::unhandled
		);
	}

}