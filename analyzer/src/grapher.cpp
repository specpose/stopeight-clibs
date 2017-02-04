// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/grapher.h"
#include <iostream>

#include "sycl/helpers/sycl_buffers.hpp"

namespace grapher {

	template<typename T>void Test2::create_sycl_buffer(size_t s)
	{
		cl::sycl::buffer<T, 1> buf = sycl::helpers::make_temp_buffer<T>(s);
	}

	template void Test2::create_sycl_buffer<float>(size_t);

}