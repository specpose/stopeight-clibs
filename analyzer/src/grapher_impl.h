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

	private:
		//not possible, cant write to pointer of std::array
		//only construct buffer later from std::vector?
		cl::sycl::buffer<T> buf;
		float* ptr;
		std::vector<float>* test;
	};
}