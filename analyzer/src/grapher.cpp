// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "grapher_impl.h"

#include "sycl/helpers/sycl_buffers.hpp"

namespace grapher {

	template<typename T> grapher::Buffer<T>::Buffer(size_t s) : buf(sycl::helpers::make_temp_buffer<T>(s))
	{
	}

	template grapher::Buffer<float>::Buffer(size_t);

	template<typename T> grapher::Buffer<T>::~Buffer() {
	}

	template grapher::Buffer<float>::~Buffer();

	template<typename T>void*const* Buffer<T>::get_sycl_buffer()
	{
		return nullptr;
	}

	template void*const* Buffer<float>::get_sycl_buffer();

}