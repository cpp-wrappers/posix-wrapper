#if 0
. `dirname ${BASH_SOURCE[0]}`/compile.sh
#endif

#include <posix/io.hpp>
#include <array.hpp>

#include <posix/default_unhandled.cpp>

int main() {
	array<char, 1024> arr{};

	while(nuint read = posix::std_in.read_to(arr)) {
		posix::std_out.write_from(arr.shrink_view(read));
		posix::std_out.write_from(c_string{"new line!\n"});
	}
}