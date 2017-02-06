#pragma once

#include "sycl/helpers/sycl_buffers.hpp"

namespace grapher {

	template<typename T>class Buffer
	{
	public:
		Buffer(size_t s);
		~Buffer();

		size_t getSize();
		void*const* get_sycl_buffer();

	private:

		cl::sycl::buffer<T, 1> buf;
	};
}