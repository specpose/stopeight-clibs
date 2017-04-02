// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#pragma once
#include <stdexcept>

namespace analyzer {
	struct alg_logic_error : std::logic_error {
		alg_logic_error(const char* what, const char* file_name, const char* function_name) : std::logic_error(what),fi_name(file_name), fu_name(function_name) {}
		const char* fi_name;
		const char* fu_name;
	};
}