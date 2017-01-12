// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "grapher_impl.h"

//#include "sycl/helpers/sycl_buffers.hpp"
//#include "CL/sycl/buffer/detail/buffer_waiter.hpp"
#include <sycl/helpers/sycl_iterator.hpp>


namespace grapher {

	template<typename T> grapher::Buffer<T>::Buffer(const T* storage, size_t size) : buf( cl::sycl::buffer<T>( storage, cl::sycl::range<1>(size) ))
	{
	}

	template grapher::Buffer<float>::Buffer(const float* storage, size_t size);
	template grapher::Buffer<double>::Buffer(const double* storage, size_t size);

	template<typename T> grapher::Buffer<T>::~Buffer() {
		//int zero = 0;
		//int error = 5 / zero;
		//get_destructor_future fails IncRef, commandgroup not yet created?
		//if omitted fails DecRef
		//buf.implementation->~buffer_waiter();
		buf.~buffer();
		//auto waiter = cl::sycl::detail::waiter<T, 1>( buf.implementation-> );
		//waiter.~buffer_waiter();
		//delete buf;
	}

	template grapher::Buffer<float>::~Buffer();
	template grapher::Buffer<double>::~Buffer();

	template<typename T> size_t Buffer<T>::size()
	{
		return buf.get_size();
	}

	template size_t Buffer<float>::size();
	template size_t Buffer<double>::size();

	template<typename T> T& Buffer<T>::at(size_t _Pos)
	{
		//array is on heap, not stack!
		auto access = buf.template get_access<cl::sycl::access::mode::write>();
		auto it = sycl::helpers::HostAccessorIterator<T, cl::sycl::access::mode::write>(access, buf.get_size());
		//auto range = buf.get_range();
		//auto range = cl::sycl::range<1>(buf.get_range());
		//return (T&)buf.data();
		//return (T&)std::get<0>(range);
		//test = new std::vector<float>(size());
		//return test->at(0);
		//ERROR
		//std::vector<float>::reference ptr2 = test->at(0);
		decltype(buf)::reference ptr2 = access[0];
		return ptr2;
	}

	template float& Buffer<float>::at(size_t _Pos);
	//template double& Buffer<double>::at(size_t _Pos);

}

//weird double defined symbol error for sycl::device from msvc
#include "algo.cpp"