#if 0
d=`dirname ${BASH_SOURCE[0]}`
root=`realpath ${d}/../`
mkdir -p ${root}/build
clang++ \
	-std=c++20 \
	-nostdinc++ \
	-nostdinc \
	-Iinclude \
	-Wall \
	-Wextra \
	-g \
	-I${root}/../core/include \
	-o ${root}/build/malloc_free_1024 \
	${BASH_SOURCE[0]}
exit 0
#endif

#include <posix/io.hpp>
#include <posix/memory.hpp>

#include <posix/__internal/default_unexpected_handler.cpp>

int main() {
	using namespace posix;

	auto memory = posix::allocate_memory_for<uint8>(1024);
}