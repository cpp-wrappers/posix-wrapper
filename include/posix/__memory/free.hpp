#pragma once

extern "C" void free(void* ptr);

namespace posix {

	inline void free_non_owning_memory(void* ptr) {
		::free(ptr);
	}

}