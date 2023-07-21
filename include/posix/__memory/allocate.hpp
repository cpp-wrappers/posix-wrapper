#pragma once

#include "./memory.hpp"
#include "../unhandled.hpp"

extern "C" void* malloc(nuint size);

namespace posix {

	template<nuint Size, nuint Alignment, typename ErrorHandler>
	requires (Size >= Alignment)
	inline span<storage_of_size_and_alignment<Size, Alignment>>
	try_allocate_raw(
		nuint elements_number, ErrorHandler&& error_handler
	) {
		void* ptr = malloc(elements_number * Size);
		if(ptr == nullptr) {
			error_handler(posix::latest_error());
			__builtin_unreachable();
		}
		return {
			(storage_of_size_and_alignment<Size, Alignment>*) ptr,
			elements_number
		};
	}

	template<typename Type, typename ErrorHandler>
	inline span<storage<Type>>
	try_allocate_raw(
		nuint elements_number, ErrorHandler&& error_handler
	) {
		return try_allocate_raw<sizeof(Type), alignof(Type)>(
			elements_number, forward<ErrorHandler>(error_handler)
		).template cast<storage<Type>>();
	}

	template<nuint Size, nuint Alignment>
	inline span<storage_of_size_and_alignment<Size, Alignment>>
	allocate_raw(nuint elements_number) {
		return try_allocate_raw<Size, Alignment>(
			elements_number, posix::unhandled
		);
	}

	template<typename Type>
	inline span<storage<Type>>
	allocate_raw(nuint elements_number) {
		return try_allocate_raw<Type>(
			elements_number, posix::unhandled
		);
	}

	template<nuint Size, nuint Alignment, typename ErrorHandler>
	inline memory_of_size_and_alignment<Size, Alignment>
	try_allocate(
		nuint elements_number, ErrorHandler&& error_handler
	) {
		span<storage_of_size_and_alignment<Size, Alignment>> s =
			try_allocate_raw<Size, Alignment>(
				elements_number,
				error_handler
			);
		return {
			s.iterator(),
			s.size()
		};
	}

	template<typename Type, typename ErrorHandler>
	inline memory<Type>
	try_allocate(
		nuint elements_number, ErrorHandler&& error_handler
	) {
		span<storage<Type>> s =
			try_allocate_raw<Type>(
				elements_number,
				error_handler
			);
		return {
			s.iterator(),
			s.size()
		};
	}

	template<nuint Size, nuint Alignment>
	inline memory_of_size_and_alignment<Size, Alignment>
	allocate(nuint elements_number) {
		return try_allocate<Size, Alignment>(
			elements_number, posix::unhandled
		);
	}

	template<typename Type = uint1a>
	inline memory<Type>
	allocate(nuint elements_number) {
		return try_allocate<Type>(
			elements_number, posix::unhandled
		);
	}

}