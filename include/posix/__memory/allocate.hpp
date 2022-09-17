#pragma once

#include "./memory.hpp"
#include "../error_handler.hpp"

extern "C" void* malloc(nuint size);
extern "C" void *calloc(nuint elements_number, nuint element_size);

namespace posix {

	template<typename ForType, typename ErrorHandler>
	inline span<ForType>
	try_allocate_non_owning_memory_of(
		nuint size, ErrorHandler&& error_handler
	) {
		nuint size_bytes = sizeof(ForType) * size;
		ForType* ptr = (ForType*) malloc(size_bytes);
		if(ptr == nullptr) {
			error_handler(posix::latest_error());
		}
		return { ptr, size };
	}

	template<typename ForType, typename ErrorHandler>
	inline span<ForType>
	try_allocate_non_owning_zeroed_memory_of(
		nuint size, ErrorHandler&& error_handler
	) {
		ForType* ptr = (ForType*) calloc(size, sizeof(ForType));
		if(ptr == nullptr) {
			error_handler(posix::latest_error());
		}
		return { ptr, size };
	}

	template<typename ForType>
	inline span<ForType>
	allocate_non_owning_memory_of(nuint size) {
		return allocate_non_owning_memory_of<ForType>(
			size, posix::error_handler
		);
	}

	template<typename ForType>
	inline span<ForType>
	allocate_non_owning_zeroed_memory_of(nuint size) {
		return allocate_non_owning_zeroed_memory_of<ForType>(
			size, posix::error_handler
		);
	}

	template<typename ForType, typename ErrorHandler>
	inline memory_for_range_of<ForType>
	try_allocate_memory_for(nuint size, ErrorHandler&& error_handler) {
		auto ptr =
			try_allocate_non_owning_memory_of<ForType>(
				size, error_handler
			).iterator();
		return { (storage<ForType>*) ptr, size };
	}

	template<typename ForType, typename ErrorHandler>
	inline memory_for<ForType>
	try_allocate_memory_for(ErrorHandler&& error_handler) {
		ForType* ptr =
			allocate_non_owning_memory_of<ForType>(
				1, error_handler
			).iterator();
		return *(memory_for<ForType>*) ptr; // not trivial, actually...
	}

	template<typename ForType>
	inline memory_for_range_of<ForType>
	allocate_memory_for(nuint size) {
		return try_allocate_memory_for<ForType>(
			size, posix::error_handler
		);
	}

	template<typename ForType>
	inline memory_for<ForType>
	allocate_memory_for() {
		return try_allocate_memory_for<ForType>(posix::error_handler);
	}

}