#pragma once

#include <vector>

#include "preloaderif.h"

namespace grapher {

	template<typename T>class Buffer : public PreloaderIF<T>
	{
	public:
		//Buffer<T>(const T* storage,size_t size);
		Buffer<T>(std::unique_ptr<std::vector<T>>& s);
		~Buffer<T>();

		/*size_t size();
		T& at(size_t _Pos);

		std::_Vector_iterator<std::_Vector_val<std::_Simple_types<T>>> rmrbegin();
		std::_Vector_iterator<std::_Vector_val<std::_Simple_types<T>>> rmrend();*/

		std::vector<T> operator()(int samplesPerPixel);


	private:
		std::unique_ptr<std::vector<T>>& buf;
	};
}