#pragma once

#include "./free.hpp"

#include <span.hpp>
#include <storage.hpp>
#include <exchange.hpp>

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
	try_allocate_memory_for(nuint size, ErrorHandler&& unexpected_handler);

	template<typename ForType0, typename ErrorHandler>
	friend inline memory_for_range_of<ForType0>
	try_allocate_zeroed_memory_for(nuint size, ErrorHandler&& unexpected_handler);

public:

	memory_for_range_of() = default;

	memory_for_range_of(memory_for_range_of<ForType>&& other)
		: base_type {
			exchange(
				(span<storage<ForType>>&) other,
				span<storage<ForType>>{}
			)
		}
	{}

	template<same_as<remove_const<ForType>> Type>
	requires type_is_const<ForType>
	memory_for_range_of(memory_for_range_of<Type>&& other)
		: base_type {
			span {
				(storage<const Type>*) other.iterator(),
				other.size()
			}
		}
	{
		exchange(
			(span<storage<ForType>>&) other,
			span<storage<ForType>>{}
		);
	}

	memory_for_range_of& operator = (memory_for_range_of&& other) {
		((base_type&) *this) = exchange((base_type&)other, base_type{});
		return *this;
	}

	~memory_for_range_of() {
		free_raw_memory((void*) base_type::iterator());
	}

	span<const ForType> as_span() const {
		return { (const ForType*) this->iterator(), this->size() };
	}
	span<      ForType> as_span()       {
		return { (      ForType*) this->iterator(), this->size() };
	}

	template<typename Type>
	span<const Type> as_span() const {
		return { (const Type*) this->iterator(), this->size() };
	}
	template<typename Type>
	span<      Type> as_span()       {
		return { (      Type*) this->iterator(), this->size() };
	}

};

}