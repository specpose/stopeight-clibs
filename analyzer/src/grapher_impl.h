#pragma once

#include "sycl/helpers/sycl_buffers.hpp"

namespace grapher {

	template<typename T>class Buffer
	{
	public:
		Buffer<T>(const T* storage,size_t size);
		~Buffer<T>();

		size_t size();
		T& at(size_t _Pos);

		sycl::helpers::BufferIterator<T, std::allocator<T>> rmrbegin();
		sycl::helpers::BufferIterator<T, std::allocator<T>> rmrend();

		//template<typename... stl_args, typename=Enable_if<sizeof...(stl_args)==0> >void execute_stl(void(*_func)(stl_args...),stl_args... _a);
		void execute_stl();


	private:
		cl::sycl::buffer<T> buf;
	};
}