#pragma once

#include "./free.hpp"

#include <span.hpp>
#include <storage.hpp>

namespace posix {

template<typename ForType>
struct memory_for : storage<ForType> {

	~memory_for() {
		free_raw_memory((void*) this->data);
	}

};

template<typename ForType>
class memory_for_range_of : public span<storage<ForType>> {
	using base_type = span<storage<ForType>>;

	memory_for_range_of(storage<ForType>* ptr, nuint size) :
		base_type{ ptr, size }
	{}

	template<typename ForType0, typename ErrorHandler>
	friend inline memory_for_range_of<ForType0>
	try_allocate_memory_for(nuint size, ErrorHandler&& error_handler);

	template<typename ForType0, typename ErrorHandler>
	friend inline memory_for_range_of<ForType0>
	try_allocate_zeroed_memory_for(nuint size, ErrorHandler&& error_handler);

public:

	memory_for_range_of() = default;

	memory_for_range_of(memory_for_range_of&& other)
		: base_type{ exchange((base_type&)other, base_type{}) }
	{}

	memory_for_range_of& operator = (memory_for_range_of&& other) {
		((base_type&) *this) = exchange((base_type&)other, base_type{});
		return *this;
	}

	~memory_for_range_of() {
		free_raw_memory((void*) base_type::iterator());
	}

	span<const ForType> as_span() const {
		return { (const ForType*) &*this->iterator(), this->size() };
	}
	span<      ForType> as_span()       {
		return { (      ForType*) &*this->iterator(), this->size() };
	}

};

}