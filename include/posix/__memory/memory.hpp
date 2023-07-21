#pragma once

#include "./free.hpp"

#include <span.hpp>
#include <storage.hpp>
#include <exchange.hpp>

namespace posix {

template<nuint Size, nuint Alignment>
class memory_of_size_and_alignment :
	public span<storage_of_size_and_alignment<Size, Alignment>>
{
	using base_type = span<storage_of_size_and_alignment<Size, Alignment>>;

	memory_of_size_and_alignment(
		storage_of_size_and_alignment<Size, Alignment>* ptr,
		nuint size
	) :
		base_type{ ptr, size }
	{}

	template<nuint Size0, nuint Alignment0, typename ErrorHandler>
	friend inline memory_of_size_and_alignment<Size0, Alignment0>
	try_allocate(
		nuint elements_number, ErrorHandler&& unexpected_handler
	);

	template<nuint Size0, nuint Alignment0, typename ErrorHandler>
	friend inline memory_of_size_and_alignment<Size0, Alignment0>
	try_allocate_zeroed(
		nuint elements_number, ErrorHandler&& unexpected_handler
	);

public:

	memory_of_size_and_alignment() = default;

	memory_of_size_and_alignment(
		memory_of_size_and_alignment&& other
	)
		: base_type {
			exchange((base_type&)other, base_type{})
		}
	{}

	memory_of_size_and_alignment& operator = (
		memory_of_size_and_alignment&& other
	) {
		((base_type&) *this) = exchange((base_type&)other, base_type{});
		return *this;
	}

	~memory_of_size_and_alignment() {
		free_raw_memory((void*) base_type::iterator());
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

template<typename Type = uint1a>
class memory : public span<storage<Type>> {
	using base_type = span<storage<Type>>;

	static constexpr bool is_borrowed_range = false;

	memory(storage<Type>* ptr, nuint size) :
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

}