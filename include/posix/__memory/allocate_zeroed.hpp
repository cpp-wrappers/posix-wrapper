#pragma once

#include "./memory.hpp"
#include "../unhandled.hpp"

extern "C" void *calloc(nuint elements_number, nuint element_size);

namespace posix {

	template<nuint Size, nuint Alignment, typename ErrorHandler>
	requires (Size >= Alignment)
	span<storage_of_size_and_alignment<Size, Alignment>>
	try_allocate_raw_zeroed(
		nuint elements_number, ErrorHandler&& unexpected_handler
	) {
		void* ptr = calloc(
			elements_number,
			Size
		);
		if(ptr == nullptr) {
			unexpected_handler(posix::latest_error());
			__builtin_unreachable();
		}
		return {
			(storage_of_size_and_alignment<Size, Alignment>*) ptr,
			elements_number
		};
	}

	template<typename Type, typename ErrorHandler>
	inline span<storage<Type>>
	try_allocate_raw_zeroed(
		nuint elements_number, ErrorHandler&& unexpected_handler
	) {
		return try_allocate_raw_zeroed<sizeof(Type), alignof(Type)>(
			elements_number,
			forward<ErrorHandler>(unexpected_handler)
		).template cast<storage<Type>>();
	}

	template<nuint Size, nuint Alignment, typename ErrorHandler>
	inline memory_of_size_and_alignment<Size, Alignment>
	try_allocate_zeroed(
		nuint elements_number, ErrorHandler&& unexpected_handler
	) {
		span<storage_of_size_and_alignment<Size, Alignment>> s =
			try_allocate_raw_zeroed<Size, Alignment>(
				elements_number, unexpected_handler
			);
		return {
			s.iterator(),
			s.size()
		};
	}

	template<typename Type, typename ErrorHandler>
	inline memory<Type>
	try_allocate_zeroed(
		nuint elements_number, ErrorHandler&& unexpected_handler
	) {
		span<storage<Type>> s =
			try_allocate_raw_zeroed<Type>(
				elements_number, unexpected_handler
			);
		return {
			s.iterator(),
			s.size()
		};
	}

	template<nuint Size, nuint Alignment>
	inline span<storage_of_size_and_alignment<Size, Alignment>>
	allocate_raw_zeroed(nuint elements_number) {
		return try_allocate_raw_zeroed<Size, Alignment>(
			elements_number, posix::unhandled
		);
	}

	template<typename Type>
	inline span<storage<Type>>
	allocate_raw_zeroed(nuint elements_number) {
		return try_allocate_raw_zeroed<Type>(
			elements_number, posix::unhandled
		);
	}

	template<nuint Size, nuint Alignment = Size>
	inline memory_of_size_and_alignment<Size, Alignment>
	allocate_zeroed(nuint elements_number) {
		return try_allocate_zeroed<Size, Alignment>(
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