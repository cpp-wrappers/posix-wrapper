#pragma once

#include "./free.hpp"

#include <span.hpp>
#include <storage.hpp>
#include <exchange.hpp>

namespace posix {

template<typename Type = uint1a>
class memory : public span<Type> {
	using base_type = span<Type>;

	static constexpr bool is_borrowed_range = false;

	memory(Type* ptr, nuint size) :
		base_type{ ptr, size }
	{}

	template<typename Type0, typename ErrorHandler>
	friend inline memory<Type0>
	try_allocate(
		nuint elements_number, ErrorHandler&& unexpected_handler
	);

	template<typename Type0, typename ErrorHandler>
	friend inline memory<Type0>
	try_allocate_zeroed(
		nuint elements_number, ErrorHandler&& unexpected_handler
	);

public:

	memory() = default;

	memory(memory&& other)
		: base_type {
			exchange((base_type&)other, base_type{})
		}
	{}

	memory& operator = (memory&& other) {
		free_raw_memory((void*) base_type::iterator());
		((base_type&) *this) = exchange((base_type&)other, base_type{});
		return *this;
	}

	~memory() {
		free_raw_memory((void*) base_type::iterator());
	}

	span<const Type> as_span() const {
		return { (const Type*) this->iterator(), this->size() };
	}
	span<      Type> as_span()       {
		return { (      Type*) this->iterator(), this->size() };
	}

};

} // posix