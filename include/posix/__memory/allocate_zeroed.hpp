#pragma once

#include "./memory.hpp"
#include "../unhandled.hpp"

extern "C"
	[[gnu::malloc]]
	[[gnu::alloc_size(2, 1)]]
	void *calloc(nuint elements_number, nuint element_size);

namespace posix {

	template<
		typename Type,
		typename SizeType = nuint,
		typename IndexType = SizeType,
		typename ErrorHandler
	>
	inline span<Type, SizeType, IndexType>
	try_allocate_raw_zeroed(
		nuint elements_number, ErrorHandler&& unexpected_handler
	) {
		void* ptr = calloc(elements_number, sizeof(Type));
		if(ptr == nullptr) {
			unexpected_handler(posix::latest_error());
			__builtin_unreachable();
		}
		return { (Type*) ptr, SizeType(elements_number) };
	}

	template<
		typename Type,
		typename SizeType = nuint,
		typename IndexType = SizeType,
		typename ErrorHandler
	>
	inline memory<Type, SizeType, IndexType>
	try_allocate_zeroed(
		nuint elements_number, ErrorHandler&& unexpected_handler
	) {
		span<Type> s = try_allocate_raw_zeroed<Type, SizeType, IndexType>(
			elements_number, unexpected_handler
		);
		return { s.iterator(), s.size() };
	}

	template<
		typename Type,
		typename SizeType = nuint,
		typename IndexType = SizeType
	>
	inline span<Type, SizeType, IndexType>
	allocate_raw_zeroed(nuint elements_number) {
		return try_allocate_raw_zeroed<Type, SizeType, IndexType>(
			elements_number, posix::unhandled
		);
	}

	template<
		typename Type = uint1a,
		typename SizeType = nuint,
		typename IndexType = SizeType
	>
	inline memory<Type, SizeType>
	allocate_zeroed(nuint elements_number) {
		return try_allocate_zeroed<Type, SizeType, IndexType>(
			elements_number, posix::unhandled
		);
	}

}