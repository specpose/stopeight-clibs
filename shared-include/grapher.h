// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef GRAPHER_H
#define GRAPHER_H

#include <memory>
#include <vector>

// grapher.h is compiled by msvc, grapher_impl.h is compiled by llvm4
// Hide everything SYCL
// For hiding and dual implementation, NAME MUST BE THE SAME
// AND NO IMPLEMENTATIONS IN HERE

#include "preloaderif.h"

namespace grapher {

	template<typename T>class Buffer : public PreloaderIF<T>
	{
	public:
		//Buffer<T>();
		Buffer<T>(std::vector<T>* s);
		~Buffer<T>();

		std::vector<T> operator()(int samplesPerPixel);
	};
}
#endif
