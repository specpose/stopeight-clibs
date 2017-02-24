#pragma once

#include "preloaderif.h"

#include "sycl/helpers/sycl_buffers.hpp"

namespace grapher {

	template<typename T>class Buffer : public PreloaderIF<T>
	{
	public:
		//Buffer<T>(const T* storage, size_t size);
		Buffer<T>(std::unique_ptr<std::vector<T>>& s);
		~Buffer<T>();

		/*size_t size();
		T& at(size_t _Pos);

		sycl::helpers::BufferIterator<T, std::allocator<T>> rmrbegin();
		sycl::helpers::BufferIterator<T, std::allocator<T>> rmrend();*/

		std::vector<T> operator()(int samplesPerPixel);


	private:
		cl::sycl::buffer<T> buf;
	};
}