// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "grapher_impl.h"

//begin()function
#include <sycl/helpers/sycl_iterator.hpp>
//begin()function


namespace grapher {

	template<typename T> grapher::Buffer<T>::Buffer(const T* storage, size_t size)
		// : buf(cl::sycl::buffer<T>())
		 : buf( cl::sycl::buffer<T>( storage, cl::sycl::range<1>(size) ))
	{
	}

	template grapher::Buffer<float>::Buffer(const float* storage, size_t size);
	template grapher::Buffer<double>::Buffer(const double* storage, size_t size);

	template<typename T> grapher::Buffer<T>::~Buffer() {
		//get_destructor_future fails IncRef, commandgroup not yet created?
		//if omitted fails DecRef
		//buf.implementation->~buffer_waiter();
		/*auto f = buf.implementation->get_destructor_future();
		if (f) {
			
			buf.implementation.reset();
			//TRISYCL_DUMP_T("~buffer_waiter() is waiting");
			// Then wait for its end in some other thread
			f->wait();
			//TRISYCL_DUMP_T("~buffer_waiter() is done");
		}*/
		//buf.~buffer();
		//delete buf;
		//auto waiter = cl::sycl::detail::waiter<T, 1>( buf.implementation-> );
		//waiter.~buffer_waiter();
		//delete buf;
	}

	template grapher::Buffer<float>::~Buffer();
	template grapher::Buffer<double>::~Buffer();

	//template<typename T> template<typename... stl_args> void Buffer<T>::execute_stl(void(*_func)(stl_args...))
	template<typename T> void Buffer<T>::execute_stl()
	{
		//sycl::sycl_heterogeneous_execution_policy<class testname> pol;
		sycl::sycl_execution_policy<> independent;
		{//sync: buffer
			cl::sycl::default_selector h; //default sycl device
										  //different queues?
			{//queue(s): it's a functor(handle)
				cl::sycl::queue sequential(h);
				//all kernels
				sycl::sycl_execution_policy<class for_each1> task1(sequential);
				//void(*_func)(decltype(buf)...);
				//_func = grapher::samples_To_VG<decltype(task1),decltype(buf), decltype(buf)>&;
				//_func(task1, sycl::helpers::begin(buf), sycl::helpers::end(buf), sycl::helpers::begin(buf));
				//grapher::samples_To_VG(task1, sycl::helpers::begin(buf), sycl::helpers::end(buf), sycl::helpers::begin(buf));//its doing queue stuff internally -> not sycl inside sycl
			}//kernels sync
		}//destruct: buffer
	}
	//specialization
	//template<> template<typename... stl_args> void Buffer<float>::execute_stl(void(*_func)(stl_args...));
	template void Buffer<float>::execute_stl();
	//explicit instantiation
	//template template void Buffer<float>::execute_stl(void(iteratorstart, iteratorend), iteratorstart, iteratorend);

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
		//auto it = sycl::helpers::HostAccessorIterator<T, cl::sycl::access::mode::write>(access, buf.get_size());
		//auto range = cl::sycl::range<1>(buf.get_range());
		//return (T&)buf.data();
		//return (T&)std::get<0>(range);
		decltype(buf)::reference ptr2 = access[0];
		return ptr2;
	}

	template float& Buffer<float>::at(size_t _Pos);
	//template double& Buffer<double>::at(size_t _Pos);

	template<typename T>
	sycl::helpers::BufferIterator<T, std::allocator<T>> Buffer<T>::rmrbegin()
	{
		return sycl::helpers::begin(buf);
	}
	template sycl::helpers::BufferIterator<float, std::allocator<float> > Buffer<float>::rmrbegin();

	template<typename T>
	sycl::helpers::BufferIterator<T, std::allocator<T>> Buffer<T>::rmrend()
	{
		return sycl::helpers::end(buf);
	}
	template sycl::helpers::BufferIterator<float, std::allocator<float> > Buffer<float>::rmrend();

}

//weird double defined symbol error for sycl::device from msvc
#include "algo.cpp"