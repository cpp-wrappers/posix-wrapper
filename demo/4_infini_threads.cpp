#if 0
. `dirname ${BASH_SOURCE[0]}`/compile.sh
#endif

#include <posix/thread.hpp>

#include <posix/default_unhandled.cpp>

int main() {
	auto f = [](void*) {
		while(true) {}
		return (void*) nullptr;
	};

	for(int i = 0; i < 3; ++i) {
		posix::create_thread(f);
	}

	f(nullptr);
}