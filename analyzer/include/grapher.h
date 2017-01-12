// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef GRAPHER_H
#define GRAPHER_H

#include "analyzer_global.h"

// grapher.h is compiled by msvc, grapher_impl.h is compiled by llvm4
// Hide everything SYCL
//#include "sycl/helpers/sycl_buffers.hpp"

namespace grapher {

	template<typename T>class Buffer
	{
	public:
		Buffer<T>(const T* storage, size_t size);
		~Buffer<T>();

		size_t size();
		T& at(size_t _Pos);

	private:
		//not possible, cant write to pointer of std::array
		//only construct buffer later from std::vector?
//		cl::sycl::buffer<T, 1> buf;
//		float* ptr;
//		std::vector<float>* test;
	};
}
#endif
