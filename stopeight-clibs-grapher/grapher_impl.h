#pragma once

#include <vector>

#include "preloaderif.h"

namespace grapher {

	template<typename T>class Buffer : public PreloaderIF<T, std::vector<std::pair<float, float>>>
	{
	public:
		Buffer<T>();
		Buffer<T>(std::vector<T>* s);
		~Buffer<T>();

		/*size_t size();
		T& at(size_t _Pos);

		std::_Vector_iterator<std::_Vector_val<std::_Simple_types<T>>> rmrbegin();
		std::_Vector_iterator<std::_Vector_val<std::_Simple_types<T>>> rmrend();*/

		std::vector<std::pair<float, float>> operator()(int samplesPerPixel);


	private:
		std::vector<T>* buf;
	};
}