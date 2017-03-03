#pragma once

#include <vector>

#include "preloaderif.h"

namespace grapher {

	template<typename T>class Buffer : public PreloaderIF<T, std::vector<std::pair<float, float>>>
	{
	public:
		Buffer<T>();
		Buffer<T>(std::vector<T>* s);
		explicit Buffer<T>(std::vector<T>* s, int showSamples, int samplesPerVector=1, double unitaryLength = 1);

		~Buffer<T>();

		/*size_t size();
		T& at(size_t _Pos);

		std::_Vector_iterator<std::_Vector_val<std::_Simple_types<T>>> rmrbegin();
		std::_Vector_iterator<std::_Vector_val<std::_Simple_types<T>>> rmrend();*/

		std::vector<std::pair<float, float>> operator()();


	private:
		std::vector<T>* buf;
		int _samplesPerVector,_showSamples;
		double _unitaryLength;
		std::pair<std::pair<double, double>, std::pair<double, double>> _center;
	};
}