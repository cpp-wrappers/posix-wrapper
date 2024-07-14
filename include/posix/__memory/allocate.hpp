#pragma once

#include "./memory.hpp"
#include "../unhandled.hpp"


extern "C" [[gnu::malloc]] [[gnu::alloc_size(1)]] void* malloc(nuint size);


namespace posix {

	template<
		typename Type,
		typename SizeType = nuint,
		typename IndexType = SizeType,
		typename ErrorHandler
	>
	inline span<Type, SizeType, IndexType>
	try_allocate_raw(
		nuint elements_number, ErrorHandler&& error_handler
	) {
		void* ptr = malloc(elements_number * sizeof(Type));
		if(ptr == nullptr) {
			error_handler(posix::latest_error());
			__builtin_unreachable();
		}
		return { (Type*) ptr, SizeType(elements_number) };
	}

	template<
		typename Type,
		typename SizeType = nuint,
		typename IndexType = SizeType
	>
	inline span<Type, SizeType, IndexType>
	allocate_raw(nuint elements_number) {
		return try_allocate_raw<Type, SizeType, IndexType>(
			elements_number, posix::unhandled
		);
	}

	template<
		typename Type,
		typename SizeType = nuint,
		typename IndexType = SizeType,
		typename ErrorHandler
	>
	inline memory<Type, SizeType, IndexType>
	try_allocate(
		nuint elements_number, ErrorHandler&& error_handler
	) {
		span<Type, SizeType> s = try_allocate_raw<Type, SizeType, IndexType>(
			elements_number,
			error_handler
		);
		return { s.iterator(), s.size() };
	}

	template<
		typename Type = uint1a,
		typename SizeType = nuint,
		typename IndexType = SizeType
	>
	inline memory<Type, SizeType, IndexType>
	allocate(nuint elements_number) {
		return try_allocate<Type, SizeType, IndexType>(
			elements_number, posix::unhandled
		);
	}

}