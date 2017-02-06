// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef GRAPHER_H
#define GRAPHER_H

#include "analyzer_global.h"

#include <iostream>

// grapher.h is compiled by msvc, grapher_impl.h is compiled by llvm4
// Hide everything SYCL
//#include "sycl/helpers/sycl_buffers.hpp"

namespace grapher {

	template<typename T>class Buffer
	{
	public:
		Buffer(size_t s);
		~Buffer();

		size_t getSize();
		void*const* get_sycl_buffer();

	private:

//		cl::sycl::buffer<T, 1> buf;
	};
}

#endif
