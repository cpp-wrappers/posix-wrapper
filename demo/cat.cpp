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
	-o ${root}/build/cat \
	${BASH_SOURCE[0]}
exit 0
#endif

#include <posix/io.hpp>
#include <array.hpp>

#include <posix/default_error_handler.cpp>

int main(int argc, char** argv) {
	using namespace posix;

	if(argc != 2) {
		std_err().write_from(c_string{ "usage: cat <path>" });
		abort();
	}

	own_file f = open_file(
		c_string{ argv[1] },
		file_access_modes{ file_access_mode::read }
	);

	array<char, 65536> data;
	while(nuint read = f->read_to(data)) {
		std_out().write_from(data, read);
	}
}