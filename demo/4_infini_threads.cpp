#if 0
d=`dirname ${BASH_SOURCE[0]}`
root=`realpath ${d}/../`
mkdir -p ${root}/build
clang++ \
	-pthread \
	-std=c++20 \
	-nostdinc++ \
	-nostdinc \
	-I${root}/include \
	-Wall \
	-Wextra \
	-g \
	-I${root}/../core/include \
	-o ${root}/build/4_infini_threads \
	${BASH_SOURCE[0]}
exit 0
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