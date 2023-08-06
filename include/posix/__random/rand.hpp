#pragma once

extern "C" void srand(unsigned seed);
extern "C" int rand();

namespace posix {

	inline void rand_seed(unsigned seed) {
		::srand(seed);
	}

	inline int rand() {
		return ::rand();
	}

}