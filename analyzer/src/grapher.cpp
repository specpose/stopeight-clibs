// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "grapher_impl.h"

//#include "sycl/helpers/sycl_buffers.hpp"
//#include "CL/sycl/buffer/detail/buffer_waiter.hpp"

namespace grapher {

	template<typename T> grapher::Buffer<T>::Buffer(size_t s) : buf(sycl::helpers::make_temp_buffer<T>(s))
	{
	}

	template grapher::Buffer<float>::Buffer(size_t);
	template grapher::Buffer<double>::Buffer(size_t);

	template<typename T> grapher::Buffer<T>::~Buffer() {
		//int zero = 0;
		//int error = 5 / zero;
		//get_destructor_future fails IncRef, commandgroup not yet created?
		//if omitted fails DecRef
		//buf.implementation->~buffer_waiter();
		//auto waiter = cl::sycl::detail::waiter<T, 1>( buf.implementation-> );
		//waiter.~buffer_waiter();
		//delete buf;
	}

	template grapher::Buffer<float>::~Buffer();
	template grapher::Buffer<double>::~Buffer();

	template<typename T>
	size_t Buffer<T>::getSize()
	{
		return buf.get_size();
	}

	template size_t Buffer<float>::getSize();
	template size_t Buffer<double>::getSize();

	template<typename T>void*const* Buffer<T>::get_sycl_buffer()
	{
		//buf.get_access(cl::sycl::access::mode::write,)
		//void*const* ptr = begin(buf);
		//return ptr;
		return nullptr;
		//return buf.implementation.get();
		//return buf.reference;
	}

	template void*const* Buffer<float>::get_sycl_buffer();
	template void*const* Buffer<double>::get_sycl_buffer();

}

//weird double defined symbol error for sycl::device from msvc
#include "algo.cpp"