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
#include <posix/abort.hpp>
#include <array.hpp>

#include <posix/default_error_handler.cpp>

int main(int argc, char** argv) {
	if(argc != 2) {
		posix::std_err.write_from(c_string{ "usage: cat <path>" });
		posix::abort();
	}

	body<posix::file> f = open_file(
		c_string{ argv[1] },
		posix::file_access_modes{ posix::file_access_mode::read }
	);

	array<char, 65536> data;
	while(nuint read = f->read_to(data)) {
		posix::std_out.write_from(data, read);
	}
}