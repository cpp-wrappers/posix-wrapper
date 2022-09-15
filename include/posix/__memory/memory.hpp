#pragma once

#include <integer.hpp>
#include <span.hpp>
#include <storage.hpp>

extern "C" void free(void* ptr);

namespace posix {

template<typename ForType>
struct memory_for : storage<ForType> {

	~memory_for() {
		::free((void*) this->data);
	}

};

template<typename ForType = uint8>
class memory_for_range_of : public span<ForType> {
	using base_type = span<ForType>;

	memory_for_range_of(ForType* ptr, nuint size) :
		base_type{ ptr, size }
	{}

	template<typename ForType0, typename ErrorHandler>
	friend inline memory_for_range_of<ForType0>
	try_allocate_memory_for(nuint size, ErrorHandler&& error_handler);

public:

	~memory_for_range_of() {
		::free((void*) base_type::iterator());
	}

};

}