#if 0
. `dirname ${BASH_SOURCE[0]}`/compile.sh
#endif

#include <posix/io.hpp>
#include <posix/abort.hpp>
#include <array.hpp>

#include <posix/default_unhandled.cpp>

int main(int argc, char** argv) {
	if(argc != 2) {
		posix::std_err.write_from(c_string{ "usage: ls <dir_path>" });
		posix::abort();
	}

	body<posix::dir> dir = posix::open_dir(c_string{argv[1]});

	handle<posix::dir_entry> entry;

	while(entry = dir->read(), entry.is_valid()) {
		posix::std_out.write_from(entry->name());
		posix::std_out.write_from(c_string{"\n"});
	}
}