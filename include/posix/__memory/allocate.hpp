#pragma once

#include "./memory.hpp"
#include "../__internal/unexpected_handler.hpp"

extern "C" void* malloc(nuint size);
extern "C" void *calloc(nuint elements_number, nuint element_size);

namespace posix {

	template<typename ForType, typename ErrorHandler>
	inline span<ForType>
	try_allocate_raw_memory_of(
		nuint size, ErrorHandler&& unexpected_handler
	) {
		nuint size_bytes = sizeof(ForType) * size;
		ForType* ptr = (ForType*) malloc(size_bytes);
		if(ptr == nullptr) {
			unexpected_handler(posix::latest_error());
			__builtin_unreachable();
		}
		return { ptr, size };
	}

	template<typename ForType, typename ErrorHandler>
	inline span<ForType>
	try_allocate_raw_zeroed_memory_of(
		nuint size, ErrorHandler&& unexpected_handler
	) {
		ForType* ptr = (ForType*) calloc(size, sizeof(ForType));
		if(ptr == nullptr) {
			unexpected_handler(posix::latest_error());
			__builtin_unreachable();
		}
		return { ptr, size };
	}

	template<typename ForType>
	inline span<ForType>
	allocate_raw_memory_of(nuint size) {
		return try_allocate_raw_memory_of<ForType>(
			size,
			[](posix::error err) { posix::unexpected_handler(err); }
		);
	}

	template<typename ForType>
	inline span<ForType>
	allocate_raw_zeroed_memory_of(nuint size) {
		return try_allocate_raw_zeroed_memory_of<ForType>(
			size,
			[](posix::error err) { posix::unexpected_handler(err); }
		);
	}

	template<typename ForType, typename ErrorHandler>
	inline memory_for_range_of<ForType>
	try_allocate_memory_for(nuint size, ErrorHandler&& unexpected_handler) {
		auto ptr =
			try_allocate_raw_memory_of<ForType>(
				size, unexpected_handler
			).iterator();
		return { (storage<ForType>*) ptr, size };
	}

	template<typename ForType, typename ErrorHandler>
	inline memory_for_range_of<ForType>
	try_allocate_zeroed_memory_for(nuint size, ErrorHandler&& unexpected_handler) {
		auto ptr =
			try_allocate_raw_zeroed_memory_of<ForType>(
				size, unexpected_handler
			).iterator();
		return { (storage<ForType>*) ptr, size };
	}

	template<typename ForType, typename ErrorHandler>
	inline memory_for<ForType>
	try_allocate_memory_for(ErrorHandler&& unexpected_handler) {
		ForType* ptr =
			allocate_raw_memory_of<ForType>(
				1, unexpected_handler
			).iterator();
		return *(memory_for<ForType>*) ptr; // not trivial, actually...
	}

	template<typename ForType>
	inline memory_for_range_of<ForType>
	allocate_memory_for(nuint size) {
		return try_allocate_memory_for<ForType>(
			size,
			[](posix::error err) { posix::unexpected_handler(err); }
		);
	}

	template<typename ForType>
	inline memory_for_range_of<ForType>
	allocate_zeroed_memory_for(nuint size) {
		return try_allocate_zeroed_memory_for<ForType>(
			size,
			[](posix::error err) { posix::unexpected_handler(err); }
		);
	}

	template<typename ForType>
	inline memory_for<ForType>
	allocate_memory_for() {
		return try_allocate_memory_for<ForType>(
			[](posix::error err) { posix::unexpected_handler(err); }
		);
	}

}