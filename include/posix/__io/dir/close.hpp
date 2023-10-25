#pragma once

#include "./types.hpp"
#include "../../error.hpp"
#include "../../unhandled.hpp"

#include <optional.hpp>
#include <body.hpp>

extern "C" int closedir(struct DIR* dirp);

namespace posix {

	inline optional<posix::error> try_close_dir(handle<posix::dir> dir_ptr) {
		int result = ::closedir((struct DIR*) dir_ptr.underlying());
		if(result == -1) {
			return { posix::latest_error() };
		}
		return {};
	}

	inline void close_dir(handle<posix::dir> dir_ptr) {
		auto result = try_close_dir(dir_ptr);
		if(result.has_value()) {
			posix::unhandled(result.get());
		}
	}

}

template<>
inline void body<posix::dir>::do_destroy() {
	posix::close_dir(this->soul_handle_);
}