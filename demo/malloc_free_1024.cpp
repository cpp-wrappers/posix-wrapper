#if 0
. `dirname ${BASH_SOURCE[0]}`/compile.sh
#endif

#include <array.hpp>

#include <posix/io.hpp>
#include <posix/memory.hpp>

#include <posix/default_unhandled.cpp>

int main() {
	using namespace posix;

	posix::memory<> memory = posix::allocate<>(1024);
}