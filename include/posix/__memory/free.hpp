#pragma once

extern "C" void free(void* ptr);

namespace posix {

	inline void free_raw_memory(void* ptr) {
		::free(ptr);
	}

}